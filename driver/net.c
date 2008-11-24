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

#include <linux/inetdevice.h>
#include <linux/notifier.h> /* struct notifier_block */
#include <linux/jiffies.h> /* jiffies, time_after, HZ */
#include <linux/module.h> /* module_param */

#include <linux/in.h> /* INADDR_LOOPBACK */
#include <linux/net.h> /* struct socket */
#include <net/sock.h> /* struct sock */

#include <linux/spinlock.h>

#include "lemona.h"

static char		*net_log_addr	= CONFIG_LEMONA_NET_LOG_SERV;
static int		net_log_port	= CONFIG_LEMONA_NET_LOG_PORT;
module_param(net_log_addr, charp, S_IRUGO);
module_param(net_log_port, int, S_IRUGO);

static int		lemona_net_activated = 0;

extern struct lemona	*juice;

static int		__lemona_net_init(void);
static void		__lemona_net_cleanup(void);

static int		lemona_net_inetaddr_notifier(struct notifier_block *,
						     unsigned long,
						     void *);

static struct notifier_block	lemona_net_inetaddr_nb = {
  .notifier_call	= lemona_net_inetaddr_notifier,
};

static inline int	lemona_net_serv_get(void)
{
  u32			a, b, c, d;

  if (sscanf(net_log_addr, "%u.%u.%u.%u", &a, &b, &c, &d) != 4)
    return (-1);
  if (a > 255 || b > 255 || c > 255 || d > 255)
    return (-1);
  return (htonl((a << 24) | (b << 16) | (c << 8) | d));
}

static int		lemona_net_inetaddr_notifier(struct notifier_block *nb,
						     unsigned long val,
						     void * data)
{
/*   struct in_ifaddr	*addr = (struct in_ifaddr *)data; */

  if (!lemona_net_activated)
    return (NOTIFY_DONE);

  /* if interface is going down... */
  if (val == NETDEV_DOWN)
    lemona_net_cleanup();

  /*
    TODO: Found a way to only cleanup when reboot/halt function are called
    to avoid overhead of releasing and reopening the socket for nothing
   */
  return (NOTIFY_DONE);
}

static int		__lemona_net_init(void)
{
  int			ret	= 0;
  struct socket		*sock	= NULL;

  if (juice->net.sock != NULL
      || (juice->net.sock == NULL
	  && !(ret = time_after(jiffies, juice->net.timeout))))
    goto out;

  ret = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
  if (ret < 0)
    {
      lemona_printk("Unable to create new socket: %i\n", ret);
      goto out;
    }
  juice->net.sock			= sock;

  ret = kernel_connect(juice->net.sock,
		       (struct sockaddr *)&(juice->net.sin),
		       sizeof(juice->net.sin), 0);
  if (ret < 0)
    {
      lemona_printk("Unable to connect to server: %i\n", ret);
      goto out;
    }
  sock->sk->sk_rcvtimeo	= 2 * HZ;
  lemona_printk("We are now connected to server %s:%d\n",
		net_log_addr, net_log_port);
 out:
  if (ret != 0)
    {
      juice->net.timeout	= jiffies + (NET_LOG_RETRY * HZ);
      __lemona_net_cleanup();
    }
  return (ret);
}

int			lemona_net_init(void)
{
  int		ret	= 0;

  mutex_init(&(juice->net.lock));

  juice->net.sin.sin_family		= AF_INET;
  juice->net.sin.sin_addr.s_addr	= lemona_net_serv_get();
  juice->net.sin.sin_port		= htons(net_log_port);

  ret = register_inetaddr_notifier(&lemona_net_inetaddr_nb);
  if (ret != 0)
    {
      lemona_printk("Unable to register notifier for inetaddr changes. "
		    "Net module will be deactivated\n");
      return (0);
    }

  mutex_lock(&(juice->net.lock));
  /* ensure timeout don't block us */
  juice->net.timeout	= jiffies - (NET_LOG_RETRY * HZ);
  __lemona_net_init();
  lemona_net_activated = 1;
  mutex_unlock(&(juice->net.lock));
  return (0);
}

/*
 * This is simply a test to check how to send something on the network.
 * Server IP/PORT should be given at module load time or during kernel config
 */
void			lemona_net_log(struct lemona_zest *zest)
{
  if (!lemona_net_activated)
    return;

  mutex_lock(&(juice->net.lock));
  if (__lemona_net_init() != 0)
    {
      mutex_unlock(&(juice->net.lock));
      return; /* couldn't get a socket working */
    }

  if (juice->net.sock)
    {
      int		ret;
      struct kvec	kvec = {
	.iov_base	= zest,
	/* Zest are aligned on sizeof(int) */
	.iov_len	= (zest->size / sizeof(int)
			   + zest->size % sizeof(int)) * sizeof(int)
      };
      struct msghdr	hdr = {
	.msg_flags	= /* MSG_DONTWAIT | */ MSG_NOSIGNAL
      };

      /*
       * TODO: if the interface used doesn't have an IP
       * and the link is broken the whole system will freeze.
       * I have no workaround so far for that. I don't even understand
       * why the kernel let us connect in the first place...
       */
      while (kvec.iov_len > 0)
	{
	  ret = kernel_sendmsg(juice->net.sock, &hdr, &kvec, 1, kvec.iov_len);
	  if (ret <= 0)
	    {
	      if (ret == -EAGAIN)
		  continue;
	      __lemona_net_cleanup();
	      if (ret != 0)
		lemona_printk("kernel_sendmsg: unable to send message: %i\n",
			      ret);
	      /* this is the time after which we will be able to try again */
	      juice->net.timeout	= jiffies + (NET_LOG_RETRY * HZ);
	      break;
	    }
	  kvec.iov_base	= (char *)zest + ret;
	  kvec.iov_len	= kvec.iov_len - ret;
	}
    }
  mutex_unlock(&(juice->net.lock));
}

static void		__lemona_net_cleanup(void)
{
  if (!juice->net.sock)
    return;
  sock_release(juice->net.sock);
  juice->net.sock	= NULL;
}

void			lemona_net_cleanup(void)
{
  mutex_lock(&(juice->net.lock));
  __lemona_net_cleanup();
  mutex_unlock(&(juice->net.lock));
}
