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

/*
 * File to be included in every kernel sources file to be patched.
 */

#ifndef _LEMONA_PATCH_H_
# define _LEMONA_PATCH_H_

# if defined(CONFIG_LEMONA) || defined(CONFIG_LEMONA_MODULE)
#  include <linux/kallsyms.h>
#  include <../lemona/lemona.h>

/*
 * add this define to avoid testing for CONFIG_LEMONA && CONFIG_LEMONA_MODULE
 */
# define LEMONA	1

/*
 * Variable
 */
extern atomic_t					lemona_activated;
#  if defined(CONFIG_LEMONA_MODULE)
static lemonalogfn				_lemona_log				= NULL;
#   if defined(LEMONA_READ)
static lemonarelayisoursfn		_lemona_relay_is_ours	= NULL;
void inline lemona_get_fn(lemonalogfn *_lemona_log,
						  lemonarelayisoursfn *_lemona_relay_is_ours)
{
  *_lemona_log = (lemonalogfn)kallsyms_lookup_name("lemona_log");
  *_lemona_relay_is_ours = (lemonarelayisoursfn)kallsyms_lookup_name("lemona_relay_is_ours");
}
#   endif /* LEMONA_READ */
#  endif /* CONFIG_LEMONA_MODULE */
# endif /* CONFIG_LEMONA || CONFIG_LEMONA_MODULE */

#endif /* _LEMONA_PATCH_H_ */
