/*
** This file is part of Lemona.
** Copyright (C) 2008 Kenfe-Mickaël Laventure
**
** The contents of this file are subject to the terms of either the
** GNU General Public License Version 2 ("GPL") or the MIT License
** (collectively, the "License"). You may not use this file except in
** compliance with the License. You can obtain a copy of the License
** at http://www.opensource.org/licenses/gpl-2.0.php and
** http://www.opensource.org/licenses/mit-license.php or GPL.LICENSE
** and MIT.LICENSE. See the License for the specific language
** governing permissions and limitations under the License.
*/

#include <errno.h>
#include <fcntl.h> /* open, posix_fallocate */
#include <stdio.h> /* snprintf */
#include <stdlib.h> /* exit */
#include <string.h> /* strerror */
#include <unistd.h> /* close, sleep */
#include <pthread.h> /* pthread_* */

#include <sys/mman.h> /* mmap, munmap */
#include <linux/limits.h> /* PATH_MAX */

#include <sys/socket.h> /* socket */
#include <sys/select.h> /* select */
#include <netinet/in.h> /* struck sockaddr_in */
#include <arpa/inet.h> /* inet_addr */

#include <netdb.h> /* gethostbyaddr */



#define SRV_PORT	4242
#define SRV_ADDRESS	"10.0.42.1"

int			current_file_nr	= 0;

struct basket {
  pthread_mutex_t	lock;
  char			file[PATH_MAX]; /* file name */
  //  void			*buf; /* Mapping */
  int			fd;
};

#define MAX_BASKET	5
 /* must be a multiple of sysconf(_SC_PAGE_SIZE) */
#define FILE_SZ		20 * 1024 * 1024
#define BUF_SZ		4096

void	basket_destroy(struct basket* basket)
{
  if (basket == NULL)
	return;

  if (basket->fd != -1)
    close(basket->fd);
  pthread_mutex_unlock(&(basket->lock));
  pthread_mutex_destroy(&(basket->lock));
}

int	preallocate_file(struct basket *basket)
{
  int	fd;
  int	ret = 0;

  if (basket->fd != -1)
    return (0); /* already preallocated */

  /* preallocate and mmap baskets */
  snprintf(basket->file, PATH_MAX, "%05d", current_file_nr);
  fd = open(basket->file, O_CREAT | O_RDWR, 0777);
  if (fd == -1)
    {
      fprintf(stderr, "mmap failed for %s: %s\n",
	      basket->file, strerror(ret));
      return (errno);
    }

  /* grow the file, for some reason fallocate doesn't exist on my linux box */
  ret = lseek(fd, FILE_SZ - 1, SEEK_SET);
  if (ret == (off_t) -1)
    {
      fprintf(stderr, "lseek failed on %s: %s\n",
	      basket->file, strerror(errno));
      close(fd);
      unlink(basket->file);
      return (errno);
    }

  if ((ret = write(fd, "", 1)) != 1)
    {
      fprintf(stderr, "Unable to grow file %s size: %s\n",
	      basket->file, strerror(errno));
      close(fd);
      unlink(basket->file);
      return (errno);
    }

  ret = lseek(fd, 0, SEEK_SET);
  if (ret == (off_t) -1)
    {
      fprintf(stderr, "lseek to offset 0 failed on %s: %s\n",
	      basket->file, strerror(errno));
      close(fd);
      unlink(basket->file);
      return (errno);
    }

  basket->fd = fd;
  ++current_file_nr;
  return (0);
}

int	basket_init(struct basket *basket)
{
  int	ret = 0;

  if (basket == NULL)
    return (EINVAL);

  memset(basket, 0, sizeof(*basket));
  basket->fd = -1;

  /* initialize and acquire the mutex */
  if ((ret = pthread_mutex_init(&(basket->lock), NULL)) != 0)
    return (ret); /* TODO: send an error message to the log */
  if ((ret = pthread_mutex_lock(&(basket->lock))) != 0)
    pthread_mutex_destroy(&(basket->lock));   /* TODO: send an error message to the log */

  ret = preallocate_file(basket);
  pthread_mutex_unlock(&(basket->lock));
  return (ret);
}

int	init_socket(void)
{
  int	ret;
  int	sock;
  struct sockaddr_in	sin;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    {
      fprintf(stderr, "Unable to create socket: %s\n", strerror(errno));
      return (sock);
    }

  ret = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ret, sizeof(ret));
  ret = 0;
  /*   setsockopt(sock, SOL_SOCKET, (void *)SO_REUSEPORT, (void *)1); */

  memset(&sin, 0, sizeof(sin));
  sin.sin_family	= AF_INET;
  sin.sin_port		= htons(SRV_PORT);
  sin.sin_addr.s_addr	= inet_addr(SRV_ADDRESS);
  ret = bind(sock, (struct sockaddr *)&sin, sizeof(sin));
  if (ret == -1)
    {
      fprintf(stderr, "Unable to bind to %s:%d: %s\n",
	      SRV_ADDRESS, SRV_PORT, strerror(errno));
      close(sock);
      return (ret);
    }

  ret = listen(sock, 1); /* we're only expecting one client ;) */
  if (ret == -1)
    {
      fprintf(stderr, "Unable to set backlog: %s\n", strerror(errno));
      close(sock);
      return (ret);
    }
  return (sock);
}


static int	init_baskets(struct basket *baskets)
{
  int		i;

  for (i = 0; i < MAX_BASKET; ++i)
    {
      if (basket_init(baskets + i) != 0)
	break;
    }

  if (i != MAX_BASKET)
    {
      for (int j = i; j >= 0; --j)
	basket_destroy(baskets + i);
    }
  return (i != MAX_BASKET);
}

void		*renew_files(void *arg)
{
  int		i;
  int		ret;
  struct basket	*baskets = (struct basket *)arg;

  while (1)
    {
      for (i = 0; i < MAX_BASKET; ++i)
	{
	  if (pthread_mutex_lock(&(baskets[i].lock)) != 0)
	    {
	      fprintf(stderr, "BUG: unable to wait for lock!\n");
	      exit(1);
	    }

	  while ((ret = preallocate_file(baskets + i)) == ENOSPC)
	    sleep(5);

	  /* something is wrong... quit right now, might be a bug */
	  if (ret != 0)
	    exit(2); /* TODO: well we should actually try to cleanup... */

	  pthread_mutex_unlock(&(baskets[i].lock));
	}
    }
}

static void		start(void)
{
  int			fd;
  int			ret;
  pthread_t		tid;
  int			sock;
  struct basket		baskets[MAX_BASKET];
  struct sockaddr_in	sin;
  struct hostent	*host;
  fd_set		readfds;
  char			buf[BUF_SZ];
  int			cur_basket;
  int			off;
  int			to_copy;
  int			new_file = 1;

  if ((sock = init_socket()) == -1)
    return;

  if (init_baskets((struct basket *)&baskets) != 0)
    {
      close(sock);
      return;
    }

  ret = pthread_create(&tid, NULL, renew_files, &baskets);
  if (ret != 0)
    {
      fprintf(stderr, "Unable to create preallocate thread: %s\n",
	      strerror(ret));
      goto out;
    }

  off = 0;
  cur_basket = 0;
  while (1)
    {
      while (1)
	{
	  pthread_mutex_lock(&(baskets[cur_basket].lock));
	  if (baskets[cur_basket].fd == -1)
	    sleep(1);
	  else
	    break;
	  pthread_mutex_unlock(&(baskets[cur_basket].lock));
	}

      fprintf(stdout, "Waiting for connections...\n");
      memset(&sin, 0, sizeof(sin));
      to_copy = sizeof(sin);
      fd = accept(sock, (struct sockaddr *)&sin, (socklen_t *)&to_copy);
      if (fd == -1)
	{
	  if  (errno == ECONNABORTED || errno == EINTR)
	    continue;
	  fprintf(stderr, "error while accepting connection: %s\n",
		  strerror(errno));
	  pthread_mutex_unlock(&(baskets[cur_basket].lock));
	  break;
	}

      host = gethostbyaddr(&(sin.sin_addr), sizeof(sin.sin_addr), AF_INET);
      fprintf(stdout, "Received a connection from %s\n",
	      host ? host->h_name : "Unknown");

      while (1)
	{
	  if (new_file)
	    {
	      fprintf(stdout, "Switching to file %s\n",
		      baskets[cur_basket].file);
	      new_file = 0;
	    }

	  FD_ZERO(&readfds);
	  FD_SET(fd, &readfds);
	  ret = select(fd + 1, &readfds, NULL, NULL, NULL);
	  if (ret == -1)
	    {
	      fprintf(stderr, "fatal select error: %s\n", strerror(errno));
	      close(baskets[cur_basket].fd);
	      baskets[cur_basket].fd = -1;
	      pthread_mutex_unlock(&(baskets[cur_basket].lock));

	      /*
		better start a new file just in case
		TODO: move current files to a backup directory
	       */
	      ++cur_basket;
	      if (cur_basket == MAX_BASKET)
		cur_basket = 0;
	      off = 0;
	      new_file = 1;

	      break;
	    }

	  if (FD_ISSET(fd, &readfds) == 0)
	    continue;

	  ret = recv(fd, buf, BUF_SZ, 0);
	  if (ret == -1)
	    {
	      fprintf(stderr, "Connection to client lost: %s\n",
		      strerror(errno));
	      close(fd);
	      baskets[cur_basket].fd = -1;
	      pthread_mutex_unlock(&(baskets[cur_basket].lock));

	      /*
		better start a new file just in case
		TODO: move current files to a backup directory
	       */
	      ++cur_basket;
	      if (cur_basket == MAX_BASKET)
		cur_basket = 0;
	      off = 0;
	      new_file = 1;

	      break;
	    }
	  if (ret == 0)
	    {
	      fprintf(stdout, "Client closed the connection\n");
	      close(fd);
	      baskets[cur_basket].fd = -1;
	      pthread_mutex_unlock(&(baskets[cur_basket].lock));

	      /*
		better start a new file just in case
		TODO: move current files to a backup directory
	       */
	      ++cur_basket;
	      if (cur_basket == MAX_BASKET)
		cur_basket = 0;
	      off = 0;
	      new_file = 1;

	      break;
	    }

	  /* copy the data to the file */
	  if (off + ret > FILE_SZ)
	    to_copy = FILE_SZ - off;
	  else
	    to_copy = ret;

	  write(baskets[cur_basket].fd, buf, to_copy);
	  off += to_copy;

	  /* switch file if needed */
	  if (to_copy != ret)
	    {
	      close(baskets[cur_basket].fd);
	      baskets[cur_basket].fd = -1;
	      pthread_mutex_unlock(&(baskets[cur_basket].lock));

	      ++cur_basket;
	      if (cur_basket == MAX_BASKET)
		cur_basket = 0;

	      pthread_mutex_lock(&(baskets[cur_basket].lock));
	      write(baskets[cur_basket].fd, buf, ret - to_copy);
	      off = ret - to_copy;
	      new_file = 1;
	    }
	}
    }
 out:
  for (int i = 0; i < MAX_BASKET; ++i)
    basket_destroy(baskets + i);
  close(sock);
}

int		main(int ac, char **av)
{

/*   switch (fork()) */
/* 	{ */
/* 	case 0: */
/* 	  start(); */
/* 	case -1: */
/* 	  fprintf(stderr, "Unable to fork: %s\n", strerror(errno)); */
/* 	default: */
/* 	  break; */
/* 	} */

  start();

  return (0);
}
