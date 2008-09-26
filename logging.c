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

#include <stdarg.h>

#include <linux/err.h>		/* ERR_PTR, PTR_ERR, IS_ERR */
#include <linux/slab.h>		/* kzalloc */
#include <linux/sched.h>	/* task_struct, current */

#include "lemona.h"

extern const struct lemona_mixer	lemona_mixers[];
extern const int			lemona_mixers_size;

static int	lemona_zest_get_size(const struct lemona_mixer *mixer,
				     bool in, va_list ap)
{
  int				i	= 0;
  int				tmp	= 0;
  int				size	= 0;
  int				bladesnr;
  const struct __lemona_mixer_handler	*handlers;

  if (unlikely(mixer == NULL))
    return (-EINVAL);

  if (in == true)
    {
      handlers	= mixer->in.handlers;
      bladesnr	= mixer->in.argnr + mixer->in.extnr;
    }
  else
    {
      handlers	= mixer->out.handlers;
      bladesnr	= mixer->out.argnr + mixer->out.extnr;
    }
  /* one blade for each arg then for each ext */
  for (i = 0; i < bladesnr; i += handlers[i].dual ? 2 : 1)
    {
      if (handlers[i].blade == NULL)
	{
	  lemona_printk("lemona_zest_get_size: Invalid mixer blade:\n");
	  lemona_printk("\tsysnr: %i\n", mixer->sysnr);
	  lemona_printk("\tblade: %i\n", i);
	  lemona_printk("\tin: %s\n",in ? "true" : "false");
	  return (-EINVAL);
	}
      if (handlers[i].dual == true)
	tmp = handlers[i].blade(NULL, false, i, 0,
				va_arg(ap, void *), va_arg(ap, void *));
      else
	tmp = handlers[i].blade(NULL, false, i, 0, va_arg(ap, void *), NULL);
      if (tmp == -1)
	{
	  lemona_printk("lemona_zest_get_size: "
			"Unable to determine argument size:\n");
	  lemona_printk("\tsysnr: %i\n", mixer->sysnr);
	  lemona_printk("\tblade: %i\n", i);
	  lemona_printk("\tin: %s\n",in ? "true" : "false");
	  return (-EINVAL);
	}
      size += tmp;
    }
  /* we're adding space for the zest itself and the args/exts size array */
  return (sizeof(struct lemona_zest) + (bladesnr * sizeof(int)) + size);
}

static int	lemona_zest_fill(const struct lemona_mixer *mixer,
				 bool in, struct lemona_zest *z,
				 va_list ap)
{
  int					i;
  int					off		= 0;
  int					ret		= 0;
  const struct __lemona_mixer_handler	*handlers;

  /* we don't check our arguments, this should have already been done */
  getnstimeofday(&(z->time));
  z->in		= in;

  z->pid	= current->pid;
  z->tgid	= current->tgid;

  z->uid	= current->uid;
  z->euid	= current->euid;
  z->fsuid	= current->fsuid;

  z->gid	= current->gid;
  z->egid	= current->egid;
  z->fsgid	= current->fsgid;

  z->sysnr	= mixer->sysnr;
  if (in == true)
    {
      z->argnr	= mixer->in.argnr;
      z->extnr	= mixer->in.extnr;
    }
  else
    {
      z->argnr	= mixer->out.argnr;
      z->extnr	= mixer->out.extnr;
    }
  z->argsz	= (int *)(z + 1);  /* located right after this struct */
  z->args	= z->argsz + z->argnr; /* located right after z->argsz */

  /*
   * Which blades to use?
   */
  if (in == true)
    handlers	= mixer->in.handlers;
  else
    handlers	= mixer->out.handlers;

  /*
   * Lets put our args into our zest
   */
  off = (int)((char *)z->args - (char *)z);
  for (i = 0; i < z->argnr; i += handlers[i].dual ? 2 : 1)
    {
      if (handlers[i].dual == true)
	ret = handlers[i].blade(z, false, i, off,
				va_arg(ap, void *), va_arg(ap, void *));
      else
	ret = handlers[i].blade(z, false, i, off, va_arg(ap, void *), NULL);
      if (ret < 0)
	  goto out;

      z->argsz[i]	= ret;
      off		= off + ret;
    }

  /*
   * Now it's the exts turn. (yes, I could have made a small function/macro)
   */
  z->extsz	= (int *)((char *)z + off); /* just after the last arg value */
  z->exts	= z->extsz + z->extnr; /* located right after z->extsz */
  off		= (int)((char *)z->exts - (char *)z);
  for (i = 0; i < z->extnr; i += handlers[i].dual ? 2 : 1)
    {
      if (handlers[i].dual == true)
	ret = handlers[i].blade(z, true, i, off,
				va_arg(ap, void *), va_arg(ap, void *));
      else
	ret = handlers[i].blade(z, true, i, off, va_arg(ap, void *), NULL);
      if (ret < 0)
	  goto out;

      z->argsz[i]	= ret;
      off		= off + ret;
    }

 out:
  return (off);
}

/**
 * lemona_zest_create - generate a new zest to be added to the log
 * @mixer: mixer to use to create this zest
 * @in: is this the entry or exit log?
 * @argnr: number of arguments of this syscall (for error checking)
 * @extnr: number of extra arguments for this syscall (for error checking)
 *
 * This is simply a generic way of handling the zest generation for
 * syscall it should avoid duplicating code in kernel patches and
 * provide for easier addition of yep unsupported syscall monitoring.
 *
 * Note, all arguments should be passed as pointer, even integers. The
 * mixers blades will be responsible on casting them in the type
 * they're expecting to handle.
 *
 * TODO: shall we pass the timespec struct here? Which mean it would
 * be computed straight after the syscall has been entered.
 */
static struct lemona_zest *lemona_zest_create(const struct lemona_mixer *mixer,
					      bool in, int argnr, int extnr,
					      va_list ap)
{
  int				zsz	= 0;
  struct lemona_zest		*z	= ERR_PTR(-ENOMEM);
  const struct __lemona_mixer	*inout;

  inout = in == true ? &(mixer->in) : &(mixer->out);
  if (inout->argnr != argnr || inout->extnr != extnr)
    {
      lemona_printk("Conflicting values for syscall %i:\n", mixer->sysnr);
      lemona_printk("argnr: %i instead of %i\n", argnr, inout->argnr);
      lemona_printk("extnr: %i instead of %i\n", extnr, inout->extnr);
      lemona_printk("in: %s\n", in ? "true" : "false");
      lemona_printk("idx: %i\n",
		    (int)((char *)mixer - (char *)lemona_mixers)
		    / sizeof(*mixer));
      return (ERR_PTR(-EINVAL));
    }
  zsz = lemona_zest_get_size(mixer, in, ap);
  if (zsz > 0)
    {
      z = kzalloc(zsz, GFP_KERNEL);
      if (z != NULL)
	z->size = zsz;
      else
	z = ERR_PTR(-ENOMEM);
    }
  return (z);
}

/**
 * lemona_log - generate a new zest and add it to the log
 * @sysnr: syscall being monitored
 * @in: is this the entry or exit log?
 * @argnr: number of arguments of this syscall (for error checking)
 * @extnr: number of extra arguments for this syscall (for error checking)
 *
 * This is simply a generic way of handling a syscall monitoring it
 * should allow us to avoid duplicating code in kernel patches and
 * provide for easier addition of yep unsupported syscall monitoring.
 *
 * NOTE: All arguments should be passed as pointer, even integers. The
 * mixers blades will be responsible to cast them in the type they're
 * expecting to handle.
 *
 * TODO: shall we pass the timespec struct here? Which mean it would
 * be computed straight after the syscall has been entered.
 */
int			lemona_log(int sysnr, bool in,
				   int argnr, int extnr, ...)
{
  va_list		ap;
  int			i;
  int			ret	= 0;
  struct lemona_zest	*z	= NULL;

  /* look for the right mixer */
  for (i = 0; i < lemona_mixers_size; ++i)
    if (sysnr == lemona_mixers[i].sysnr)
      break;
  /* none? get out of here */
  if (i == lemona_mixers_size)
    {
      lemona_printk("No mixer found for syscall: %i\n", sysnr);
      return (-EINVAL);
    }

  /* let's mix! */
  va_start(ap, extnr);
  z = lemona_zest_create(lemona_mixers + i, in, argnr, extnr, ap);
  if (IS_ERR(z))
    {
      ret = PTR_ERR(z);
      goto out; /* TODO: What should we do in this case? */
    }

  /*
   * We need to reset the ap to the beginning of the arguments
   * before trying to fill our zest.
   */
  va_end(ap);
  va_start(ap, extnr);
  ret = lemona_zest_fill(lemona_mixers + i, in, z, ap);
  if (ret != z->size)
    {
      lemona_printk("zest_fill returned a different "
		    "value than zest_get_size: %i instead of %i\n",
		    ret, z->size);
      ret = -EINVAL;
      goto out;
    }

  /*
   * TODO: call the different logging facilities:
   *  - lemona_relay_log
   *  - ...
   */
  ret = lemona_relay_log(z);

 out:
  va_end(ap);
  kfree(z); /* it handles NULL pointer, no worries ;-) */
  return (ret);
}

