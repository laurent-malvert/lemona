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


int	lemona_blade_integer(struct lemona_zest *zest,
			     bool isExt, int idx, int off,
			     void *fruit1, void *fruit2)
{
  int	val = (int)fruit1;
  int	*sz;

  /* shall we compute the size or fill the zest ? */
  if (zest == NULL)
    return (sizeof(val));

  /* fill the zest */
  sz = isExt == false ? zest->argsz : zest->extsz;
  sz[idx] = sizeof(val);
  *((int *)((char *)zest + off)) = val;

  return (sizeof(val));
}

/* this is a dual blade */
int	lemona_blade_output_buffer(struct lemona_zest *zest,
				   bool isExt, int idx, int off,
				   void *fruit1, void* fruit2)
{
  size_t	size	= (int)fruit1;
  int		*sz;
  unsigned long	uncopied;

  /* shall we compute the size or fill the zest ? */
  if (zest == NULL)
    return (sizeof(size) + size);

  /* fill the zest */
  sz = isExt == false ? zest->argsz : zest->extsz;
  sz[idx] = sizeof(size);
  sz[idx + 1] = size;

  *((int *)((char *)zest + off)) = size;
  uncopied = copy_from_user((char *)zest + off + sizeof(size),
			    fruit2, size);
  if (uncopied == size)
    return (-1);
  return (sizeof(size) + size);
}
