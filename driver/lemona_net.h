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

#ifndef _LEMONA_NET_H_
# define _LEMONA_NET_H_

# if defined(CONFIG_LEMONA_NET_LOG)

#  include <linux/in.h>		/* AF_INET, IPPROTO_TCP, struct sockaddr_in */
#  include <linux/net.h>	/* SOCK_STREAM */
#  include <linux/socket.h>	/* sock_*, kernel_* */

#  include <linux/mutex.h>	/* take a guess ;-) */


/*
 * This can be overrided via the kernel config or module parameter
 */
#  ifndef CONFIG_LEMONA_NET_LOG_SERV
#   define CONFIG_LEMONA_NET_LOG_SERV	"127.0.0.1"
#  endif

/*
 * This can be overrided via the kernel config or module parameter
 */
#  ifndef CONFIG_LEMONA_NET_LOG_PORT
#   define CONFIG_LEMONA_NET_LOG_PORT	4242
#  endif

/* How many seconds shall we wait before trying to reconnect to the server? */
# define NET_LOG_RETRY	60

struct lemona_net {
  struct mutex		lock;
/*   spinlock_t		lock; */
  unsigned long		timeout;

  struct sockaddr_in	sin;
  struct socket		*sock;
};

int	lemona_net_init(void);
void	lemona_net_log(struct lemona_zest *zest);
void	lemona_net_cleanup(void);

# else /* CONFIG_LEMONA_NET_LOG */

struct lemona_net { };

# define lemona_net_init()	-1
# define lemona_net_log(x)
# define lemona_net_cleanup()

# endif /* CONFIG_LEMONA_NET_LOG */

#endif
