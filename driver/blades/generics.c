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
 * lemona_blade_integer - add a 32 bits integer value to a zest
 * @zest: The zest to be filled
 * @isExt: Is this part of the extended arguments?
 * @idx: Index of the value in the zest
 * @off: Offset relative to the zest at which to copy the value
 * @fruit1: The value to be copied (32 bits)
 * @fruit2: Unused
 */
int		lemona_blade_integer(struct lemona_zest *zest,
				     int isExt, int idx, int off,
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

/**
 * lemona_blade_integer64 - add a 64 bits integer value to a zest
 * @zest: The zest to be filled
 * @isExt: Is this part of the extended arguments?
 * @idx: Index of the value in the zest
 * @off: Offset relative to the zest at which to copy the value
 * @fruit1: The value to be copied (64 bits)
 * @fruit2: Unused
 */
int		lemona_blade_integer64(struct lemona_zest *zest,
				       int isExt, int idx, int off,
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

int		lemona_blade_long(struct lemona_zest *zest,
				  int isExt, int idx, int off,
				  void *fruit1, void *fruit2)
{
  long	val = *((long *)fruit1);
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


/*
 * TODO: make this an alias to lemona_blade_integer64
 */
int		lemona_blade_long_long(struct lemona_zest *zest,
				       int isExt, int idx, int off,
				       void *fruit1, void *fruit2)
{
  long long		val = *((long long *)fruit1);
  int			*sz;

  /* shall we compute the size or fill the zest ? */
  if (zest == NULL)
    return (sizeof(val));

  /* fill the zest */
  sz = isExt == false ? zest->argsz : zest->extsz;
  sz[idx] = sizeof(val);
  *((int *)((char *)zest + off)) = val;

  return (sizeof(val));
}

/**
 * lemona_blade_output_buffer - add the size and buffer content to a zest
 * @zest: The zest to be filled
 * @isExt: Is this part of the extended arguments?
 * @idx: Starting index of the arguments
 * @off: Offset relative to the zest from which to copy the data
 * @buf: The buffer addresse (need to be an userspace address)
 * @len: Size of the buffer (32 bits). If < 0, it corresponds to an ERRNO
 *
 * If size is negative, the return value should be sizeof(ssize_t)
 *
 * NOTE: As you would have guessed this is a dual blade.
 */
int		lemona_blade_output_buffer(struct lemona_zest *zest,
					   int isExt, int idx, int off,
					   void __user *buf, void *len)
{
  ssize_t	size	= *((int *)len);
  int		*sz;
  unsigned long	uncopied = size;

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
				buf, size);

      if (uncopied)
	{
	  lemona_printk("(syscall %i) "
			"output_buffer: %p/%p copied %i instead of %i\n",
			zest->sysnr, buf, len,
			(int)(size - uncopied), (int)size);
	  return (-1);
	}
    }
  return (sizeof(size) + (size >= 0 ? size : 0));
}

/**
 * lemona_blade_output_buffer64 - add the size and buffer content to a zest
 * @zest: The zest to be filled
 * @isExt: Is this part of the extended arguments?
 * @idx: Starting index of the arguments
 * @off: Offset relative to the zest from which to copy the data
 * @buf: The buffer addresse (need to be an userspace address)
 * @len: Size of the buffer (64 bits). If < 0, it corresponds to an ERRNO
 *
 * If size is negative, the return value should be sizeof(s64).
 *
 * NOTE: As you would have guessed this is a dual blade.
 */
int	lemona_blade_output_buffer64(struct lemona_zest *zest,
				     int isExt, int idx, int off,
				     void *buf, void *len)
{
  s64		size	= *((u64 *)len);
  int		*sz;
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
				buf, size);
      if (uncopied)
	return (-1);
    }
  return (sizeof(size) + (size >= 0 ? size : 0));
}
