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

#ifndef _LEMONA_H_
# define _LEMONA_H_

# include <linux/time.h>	/* struct timespec */

# include "lemona_relay.h"

/*
 * So it'll be easier to spot lemona messages.
 *
 * The token paste operator (i.e. ##) is used to avoid a warning if no
 * trailing arguments are provided (see the GCC C Extension manual).
 */
# define LEMONA_PRINTK_PREFIX	" -==Lemona==- "
# define lemona_printk(s, ...)	printk(LEMONA_PRINTK_PREFIX s, ## __VA_ARGS__)

/*
 * Every single log entry is represented by a zest.
 */
struct zest {
  int			size;  	/* size taken by this zest and args sz/value */

  bool			in;
  struct timespec	time;	/* call start/end time (getnstimeofday) */

  pid_t			pid;	/* actual pid */
  pid_t 		tgid;	/* thread group id */

  uid_t			uid,euid,fsuid;	/* don't care about the suid ? */
  gid_t			gid,egid,fsgid;	/* don't care about the sgid ? */

  int			sysnr; 	/* syscall id */
  int			argnr;	/* number of args */

  /*
   * Pointer to an array of int indicating the size taken by each
   * argument this table is located directy after this structure.
   */
  int			*argsz;
  /*
   * Pointer to the first argument value. its should be placed just
   * after the end of argsz. Every args value are one after the
   * other.
   */
  void			*args;

  int			extnr;	/* extra value number */
  int			*extsz;	/* size of each extension */
  void			*exts;	/* extra values. located after the last arg */
};

/*
 * We're going to have one handler for each arg/ext.
 */
/*
 * These functions are used in two different maneers:
 *  - if dest is NULL, the space required by the argument is to be returned
 *  - if dest is not NULL, the argument should be placed in the structure
 *    and the number of written byte returned (this should match the value
 *    returned if zest was to be NULL).
 */
typedef int	(*bladefn)(void *dest, void* fruit);

struct __mixer {
  int		argnr;
  int		extnr;
  bladefn	blades[4];
};

/*
 * We have several mixer, one for each syscall. We use the array
 * declared in mixers.c to have a kind of automated way of logging
 * syscall events.
 */
struct mixer {
  int			sysnr;
  struct __mixer	in;
  struct __mixer	out;
} __attribute__((packed));

/*
 * Contains all information needed by lemona throughout the module.
 */
struct lemona {
  struct lemona_relay	relay;
};

#endif
