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


int		lemona_blade_integer(struct lemona_zest *zest,
							 bool isExt, int idx, int off,
							 void *fruit1, void *fruit2)
{
  int	val = *((int *)fruit1);
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

int		lemona_blade_integer64(struct lemona_zest *zest,
							   bool isExt, int idx, int off,
							   void *fruit1, void *fruit2)
{
  u64	val = *((u64 *)fruit1);
  int	*sz;

  /* shall we compute the size or fill the zest ? */
  if (zest == NULL)
    return (sizeof(val));

  /* fill the zest */
  sz = isExt == false ? zest->argsz : zest->extsz;
  sz[idx] = sizeof(val);
  *((u64 *)((char *)zest + off)) = val;

  return (sizeof(val));
}

/* this is a dual blade */
int		lemona_blade_output_buffer(struct lemona_zest *zest,
								   bool isExt, int idx, int off,
								   void *fruit1, void* fruit2)
{
  size_t		size	= *((int *)fruit1);
  int			*sz;
  unsigned long	uncopied;

  /* shall we compute the size or fill the zest ? */
  if (zest == NULL)
    return (sizeof(size) + (size >= 0 ? size : 0));

  /* fill the zest */
  sz = isExt == false ? zest->argsz : zest->extsz;
  sz[idx] = sizeof(size);
  *((int *)((char *)zest + off)) = size;

  /* try to copy only if we actually got something to copy */
  if (size > 0)
    {
      sz[idx + 1] = size;

      uncopied = copy_from_user((char *)zest + off + sizeof(size),
								fruit2, size);
      if (uncopied)
		{
		  lemona_printk("Copied %i instead of %i\n", size - uncopied, size);
		  return (-1);
		}
    }
  return (sizeof(size) + (size >= 0 ? size : 0));
}

/* this is a dual blade */
/*
for an unknown reason, argument order seem to be inversed by va_arg()...
*/
int	lemona_blade_output_buffer64(struct lemona_zest *zest,
								 bool isExt, int idx, int off,
								 void *fruit2, void* fruit1)
{
  u64			size	= *((u64 *)fruit1);
  int			*sz;
  unsigned long	uncopied;

  /* shall we compute the size or fill the zest ? */
  if (zest == NULL)
    return (sizeof(size) + (size >= 0 ? size : 0));

  /* fill the zest */
  sz = isExt == false ? zest->argsz : zest->extsz;
  sz[idx] = sizeof(size);
  *((u64 *)((char *)zest + off)) = size;

  /* try to copy only if we actually got something to copy */
  if (size > 0)
    {
      sz[idx + 1] = size;

      uncopied = copy_from_user((char *)zest + off + sizeof(size),
				fruit2, size);
      if (uncopied)
		{
		  lemona_printk("Access: %i Addr: %p/%p Copied %i instead of %i\n",
						access_ok(VERIFY_READ, fruit2, size),
						fruit1,
						fruit2,
						(int)size - uncopied, (int)size);
		  return (-1);
		}
    }
  return (sizeof(size) + (size >= 0 ? size : 0));
}
