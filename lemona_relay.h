/*
** This file is part of Lemona.
** Copyright (C) 2008 Kenfe-Micka�l Laventure
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

#ifndef _LEMONA_RELAY_H_
# define _LEMONA_RELAY_H_

# ifdef CONFIG_LEMONA_RELAY

/*
 * This can be override via the kernel config or module parameter
 */
#  ifndef CONFIG_LEMONA_DEBUGFS_DIR
#   define CONFIG_LEMONA_DEBUGFS_DIR	"lemona"
#  endif

/*
 * Size of a sub-buffer in relay?
 */
#  ifndef CONFIG_LEMONA_RELAY_SBUF_SZ
#   define CONFIG_LEMONA_RELAY_SBUF_SZ	(256 * 1024)
#  endif

/*
 * Number of sub-buffer in relay?
 */
#  ifndef CONFIG_LEMONA_RELAY_SBUF_NR
#   define CONFIG_LEMONA_RELAY_SBUF_NR	(4)
#  endif

/*
 * Since a log entry is a zest, lot of them give us a lemon, right...?
 */
# define LEMONA_RELAY_CHANNEL_NAME	"lemon"

struct lemona_relay {
  /*
   * Hold the struct returned by debugfs during init.
   * The directory will use the value of CONFIG_LEMONA_DEBUGFS_DIR.
   * This is overridable during module loading and from the kernel config.
   */
  struct dentry	*dir;
  /*
   * Structure designing the channel created by relay for us to use
   */
  struct rchan	*chan;
};

#  define rchan		relay.chan
#  define dfs_dir	relay.dir

struct lemona_zest;

int __init	lemona_relay_init(void);
void		lemona_relay_cleanup(void);
int		lemona_relay_log(const struct lemona_zest *);

# else /*  CONFIG_LEMONA_RELAY */

struct lemona_relay { };

#  define lemona_relay_init()	 0
#  define lemona_relay_cleanup()
#  define lemona_relay_log(z)	0

# endif /* CONFIG_LEMONA_RELAY */

#endif
