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

# include "lemona_relay.h"


struct zest {
  int	size;  	/* size taken by this zest along with args value */
  int	sysnr; 	/* syscall id */
  int	argnr;	/* number of args */
  /*
   * pointer to an array of int indicating the size taken by each argument
   * this table is located directy after this structure.
   */
  int	*argsz;
  /*
   * pointer to the first argument value. its should be placed just after
   * the end of paramsz. Every args value are one after the other.
   */
  void	*args;
  /* missing values
   * pid
   * tid
   * uid
   * cmd line
   * time (in / out)
   */
};

/*
 * Contains all information needed by lemona throughout the module
 */
struct lemona {
  struct lemona_relay	relay;
};

#endif
