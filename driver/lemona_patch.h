/*
** This file is part of Lemona.
** Copyright (C) 2008 Kenfe-Mickaël Laventure, Laurent Malvert
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
#  define LEMONA	1

/*
 * Variable
 */
extern atomic_t			lemona_activated;

#  define lemona_block_start			\
  if (atomic_read(&lemona_activated) != 0)	\
    {


#  define lemona_log_in(sysnr, argnr, extnr, ...)	__lemona_log(sysnr, true, argnr, extnr, ## __VA_ARGS__)
#  define lemona_log_out(sysnr, argnr, extnr, ...)	__lemona_log(sysnr, false, argnr, extnr, ## __VA_ARGS__)

#  if defined(CONFIG_LEMONA_MODULE)

static lemonalogfn		_lemona_log		= NULL;

#   define lemona_block_end			\
    }						\
  else						\
    {						\
      _lemona_log = NULL;			\
    }

#   define __lemona_log(sysnr, in, argnr, extnr, ...)	{		\
  if (_lemona_log == NULL)						\
    _lemona_log = (lemonalogfn)kallsyms_lookup_name("lemona_log");	\
  _lemona_log(sysnr, in, argnr, extnr, ## __VA_ARGS__);		        \
}

#   if defined(LEMONA_READ)
static lemonarelayisoursfn	_lemona_relay_is_ours	= NULL;

#    if defined(CONFIG_LEMONA_RELAY)
inline bool	lemona_relay_is_ours(const struct dentry* d)
{
  if (_lemona_relay_is_ours == NULL)
    _lemona_relay_is_ours = (lemonarelayisoursfn)kallsyms_lookup_name("lemona_relay_is_ours");
  return (_lemona_relay_is_ours(d));
}
#    endif /* CONFIG_LEMONA_RELAY */
#   endif /* LEMONA_READ */
#  else /* CONFIG_LEMONA_MODULE (i.e. CONFIG_LEMONA defined) */

#   define lemona_block_end			\
    }

#   if defined(CONFIG_LEMONA_RELAY)
#    define lemona_relay_is_ours(d) __lemona_relay_is_ours(d)
#   endif

#   define __lemona_log(sysnr, in, argnr, extnr, ...)	lemona_log(sysnr, in, argnr, extnr, ## __VA_ARGS__)

#  endif /* CONFIG_LEMONA_MODULE */

# else /* CONFIG_LEMONA || CONFIG_LEMONA_MODULE */

#  define lemona_block_start
#  define lemona_block_end

#  define lemona_log_in(sysnr, argnr, extnr, ...)
#  define lemona_log_out(sysnr, argnr, extnr, ...)

# endif /* CONFIG_LEMONA || CONFIG_LEMONA_MODULE */

#endif /* _LEMONA_PATCH_H_ */
