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

#ifndef _LEMONA_RELAY_H_
# define _LEMONA_RELAY_H_

# ifdef CONFIG_LEMONA_RELAY

/*
 * This can be override via the kernel config or module parameter
 */
#  ifndef CONFIG_LEMONA_DEBUGFS_DIR
#   define CONFIG_LEMONA_DEBUGFS_DIR	"lemona"
#  endif

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

int __init	lemona_relay_init(void);
void		lemona_relay_cleanup(void);


# else

struct lemona_relay { };

#  define lemona_relay_init()
#  define lemona_relay_cleanup()

# endif


#endif
