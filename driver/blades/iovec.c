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

#include <linux/uaccess.h> /* copy_from_user */

#include "../lemona.h"

/**
 * lemona_blade_iovec - Add the io vector to the zest
 * @zest: The zest to be filled
 * @isExt: Is this part of the extended arguments?
 * @idx: Starting index of the arguments
 * @off: Offset relative to the zest from which to copy the data
 * @iov: Start of the io vector
 * @vlen: Size of the io vector
 *
 * If called from a call entry (zest->in == true), only append the
 * vector content to the zest.
 *
 * If called from a call exit (zest->in == false), only append the
 * data pointed by the vector. /!\ In this case, the number of bytes
 * to be copied if to be fetch from the value stored at the previous
 * idx.
 *
 * NOTE: As you would have guessed this is a dual blade.
 */
int		lemona_blade_iovec(struct lemona_zest *zest,
				   int isExt, int idx, int off,
				   void *iov, void *vlen)
{
  /* TODO: code lemona_blade_iovec */
  return (0);
}
