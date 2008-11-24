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

#include <linux/fs.h>			/* struct file */
#include <linux/slab.h>			/* kzalloc */
#include <linux/limits.h>		/* PATH_MAX */
#include <linux/file.h>			/* struct file, fget_light, fput_light */
#include <linux/uaccess.h>		/* strncopy_from_user */

#include "../lemona.h"

/**
 * lemona_blade_string_null - Append the content of a null terminated string
 * @zest: The zest to be filled
 * @isExt: Is this part of the extended arguments?
 * @idx: Index of the string in the arguments
 * @off: Offset relative to the zest from which to copy the data
 * @str: String address (user space address)
 * @unused: well... it's unused ;-)
 *
 * TODO: shall we return PATH_MAX instead of getting the real size?
 * Is speed better than wasted space in zest?
 */
int		lemona_blade_string_null(struct lemona_zest *zest,
					 int isExt, int idx, int off,
					 void __user *str, void *unused)
{
  long		len;
  int		*sz;

  /* shall we compute the size or fill the zest ? */
  if (zest == NULL)
    {
      char	*buf;

      buf = kzalloc(PATH_MAX, GFP_KERNEL);
      if (buf == NULL)
	return (-ENOMEM);

      len = strncpy_from_user(buf, str, PATH_MAX);
      kfree(buf);
      return (len + 1); /* add place for \0 since strncpy copy it too */
    }

  /* fill the zest */
  sz = isExt == false ? zest->argsz : zest->extsz;
  /* copy and get size */
  len = strncpy_from_user((char *)zest + off, str, PATH_MAX);
  sz[idx] = len + 1; /* don't forget the \0, since it is copied too */
  return (len + 1);
}

/**
 * lemona_blade_string_fd - Append the path of a file descriptor
 * @zest: The zest to be filled
 * @isExt: Is this part of the extended arguments?
 * @idx: Index of the string in the arguments
 * @off: Offset relative to the zest from which to copy the data
 * @pfd: Pointer to the fd
 * @unused: well... it's unused ;-)
 *
 * TODO: do we need to lock the dentry while going through it?
 */
int		lemona_blade_string_fd(struct lemona_zest *zest,
				       int isExt, int idx, int off,
				       void *pfd, void *unused)
{
  long		fd		= *((long *)pfd);
  int		size	= 0;
  struct file	*file;
  struct dentry	*dentry;
  int		fput_needed;
  char		*dest;
  int		*sz;

  /* if the fd is invalid no need to go further */
  if (fd < 0 || (file = fget_light(fd, &fput_needed)) == NULL)
    return (size);

  dentry = file->f_dentry;

  /* TODO: shall we compute the size or fill the zest ? */
  if (zest == NULL)
    {
      while (dentry != dentry->d_parent)
	{
	  /* add space for '/' separator */
	  size			+= (int)dentry->d_name.len + (size ? 1 : 0);
	  dentry		= dentry->d_parent;
	}

      fput_light(file, fput_needed);
      return (size + 1); /* add '/' (i.e. root path) */
    }

  /* fill the zest */
  sz	= isExt == false ? zest->argsz : zest->extsz;
  dest	= (char *)zest + off;
  while (dentry != dentry->d_parent)
    {
      /* add '/' separator if needed */
      if (size)
	dest[size++]		= '/';
      strncpy(dest + size, dentry->d_name.name, dentry->d_name.len);
      size				+= (int)dentry->d_name.len;
      dentry			= dentry->d_parent;
    }
  /* add '/' (i.e. root path) */
  dest[size++]	= '/';
  sz[idx]		= size;
  fput_light(file, fput_needed);
  return (size);
}
