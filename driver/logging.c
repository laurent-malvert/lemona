/*
** This file is part of Lemona.
** Copyright (C) 2008 Kenfe-Micka�l Laventure
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

#include <stdarg.h>			/* va_* */

#include <linux/err.h>		/* ERR_PTR, PTR_ERR, IS_ERR */
#include <linux/slab.h>		/* kzalloc */
#include <linux/sched.h>	/* task_struct, current */

#include "lemona.h"

extern const struct lemona_mixer	lemona_mixers[];
extern const int			lemona_mixers_size;

#if defined (CONFIG_LEMONA_MODULE)
atomic_t				lemona_clients	= ATOMIC_INIT(0);
# define lemona_clients_inc() atomic_inc(&lemona_clients)
# define lemona_clients_dec() atomic_dec(&lemona_clients)
#else
# define lemona_clients_inc(x)
# define lemona_clients_dec(x)
#endif

/**
 * lemona_zest_get_size - Compute the size needed by a zest
 * @mixer: The mixer containing information on how to handle this zest values
 * @in: Is this at the entry or exit of a call?
 * @ap: Beginning of the arguments
 *
 * For each argument, the corresponding blade will be invoked with a
 * NULL zest as parameter. This will hint the blade to simply return
 * the size required to store the current argument value. All returned
 * values are then added together along with the lemona_zest struct
 * size and the space needed to hold the size of each value.
 */
static int	lemona_zest_get_size(const struct lemona_mixer *mixer,
				     int in, va_list ap)
{
  int					i	= 0;
  int					j	= 0;
  int					tmp	= 0;
  int					size	= 0;
  int					argnr	= 0;
  int					bladesnr;
  const struct __lemona_mixer_handler	*handlers;
  void					*arg1, *arg2;

  if (unlikely(mixer == NULL))
    return (-EINVAL);

  if (in == true)
    {
      argnr     = mixer->in.argnr;
      handlers	= mixer->in.handlers;
      bladesnr	= mixer->in.argnr + mixer->in.extnr;
    }
  else
    {
      argnr     = mixer->out.argnr;
      handlers	= mixer->out.handlers;
      bladesnr	= mixer->out.argnr + mixer->out.extnr;
    }
  /* one blade for each arg then for each ext */
  for (i = 0, j = 0; j < bladesnr; j += handlers[i].dual ? 2 : 1, ++i)
    {
      if (handlers[i].blade == NULL)
	{
	  lemona_printk("lemona_zest_get_size: Invalid mixer blade:\n");
	  lemona_printk("\tsysnr: %i\n", mixer->sysnr);
	  lemona_printk("\tblade: %i\n", i);
	  lemona_printk("\tin: %s\n", in ? "true" : "false");
	  return (-EINVAL);
	}
      arg1 = va_arg(ap, void*);
      if (handlers[i].dual == true)
	{
	  arg2	= va_arg(ap, void*);
	  tmp	= handlers[i].blade(NULL, i > argnr, -1, 0, arg1, arg2);
	}
      else
	tmp	= handlers[i].blade(NULL, i > argnr, -1, 0, arg1, NULL);
      if (tmp < 0)
	{
	  lemona_printk("lemona_zest_get_size: "
			"Unable to determine argument size:\n");
	  lemona_printk("\tsysnr: %i\n", mixer->sysnr);
	  lemona_printk("\tblade: %i\n", i);
	  lemona_printk("\tin: %s\n", in ? "true" : "false");
	  lemona_printk("\tret: %i\n", tmp);
	  return (tmp);
	}
      size += tmp;
    }
  /* we're adding space for the zest itself and the args/exts size array */
  return (sizeof(struct lemona_zest) + (bladesnr * sizeof(int)) + size);
}

/**
 * lemona_zest_fill - Fill a zest with the values pointed by ap
 * @mixer: The mixer containing information on how to handle this zest values
 * @in: Is this at the entry or exit of a call?
 * @z: The zest to be filled (has been allocated by lemona_zest_create)
 * @ap: Beginning of the arguments
 *
 * This will fill the zest with common info then invoke the differents
 * blades to copy the needed arguments in the zest buffer.
 *
 * NOTE: the timestamp is only generated in saved at this point so
 * far. It might be moved earlier in the code path later on.
 */
static int	lemona_zest_fill(const struct lemona_mixer *mixer,
				 int in, struct lemona_zest *z,
				 va_list ap)
{
  int					i;
  int					j;
  int					off		= 0;
  int					ret		= 0;
  const struct __lemona_mixer_handler	*handlers;
  void					*arg1, *arg2;

  strncpy(z->magic, "ZeSt", 4);

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
  for (i = 0, j = 0; j < z->argnr; j += handlers[i].dual ? 2 : 1, ++i)
    {
      arg1 = va_arg(ap, void*);
      if (handlers[i].dual == true)
	{
	  arg2	= va_arg(ap, void*);
	  ret	= handlers[i].blade(z, false, j, off, arg1, arg2);
	}
      else
	ret	= handlers[i].blade(z, false, j, off, arg1, NULL);
      if (ret < 0)
	{
	  lemona_printk("args (syscal %i) in: %i blade %i returned -1\n",
			mixer->sysnr, in, i);
	  goto out;
	}
      off		= off + ret;
    }

  /*
   * Now it's the exts turn. (yes, I could have made a small function/macro)
   */
  z->extsz	= (int *)((char *)z + off); /* just after the last arg value */
  z->exts	= z->extsz + z->extnr; /* located right after z->extsz */
  off		= (int)((char *)z->exts - (char *)z);
  /* don't reinit i, the idx is correct and take dual blades in account */
  for (j = 0; j < z->extnr; j += handlers[i].dual ? 2 : 1, ++i)
    {
      arg1 = va_arg(ap, void*);
      if (handlers[i].dual == true)
	{
	  arg2	= va_arg(ap, void*);
	  ret	= handlers[i].blade(z, true, j, off, arg1, arg2);
	}
      else
	ret	= handlers[i].blade(z, true, j, off, arg1, NULL);
      if (ret < 0)
	{
	  lemona_printk("exts (syscal %i) in: %i blade %i returned %i\n",
			mixer->sysnr, in, i, ret);
	  goto out;
	}
      off		= off + ret;
    }

 out:
  return (ret < 0 ? ret : off);
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
 * TODO: shall we pass the timespec struct here? Which mean it would
 * be computed straight after the syscall has been entered.
 */
static struct lemona_zest *lemona_zest_create(const struct lemona_mixer *mixer,
					      int in, int argnr, int extnr,
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
      int	alignedsz;

      /* aligned the allocation */
      alignedsz	= (zsz / sizeof(int) + zsz % sizeof(int)) * sizeof(int);
      z		= kzalloc(alignedsz, GFP_KERNEL);
      if (z != NULL)
	z->size		= zsz;
      else
	{
	  lemona_printk("(syscall %i) Unable to create zest with size: %i\n",
			mixer->sysnr, zsz);
	  z = ERR_PTR(-ENOMEM);
	}
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
int			lemona_log(int sysnr, int in,
				   int argnr, int extnr, ...)
{
  va_list		ap;
  int			i;
  int			ret	= 0;
  struct lemona_zest	*z	= NULL;

  lemona_clients_inc();

  /* look for the right mixer */
  if (likely(sysnr < lemona_mixers_size
	     && lemona_mixers[sysnr].sysnr == sysnr))
    i = sysnr;
  else if (unlikely(lemona_mixers[sysnr].sysnr != sysnr
		    && lemona_mixers[sysnr].sysnr != -1)) /* uhuh... */
    {
      lemona_printk("Mixer array is corrupted: %i != %i (%i total)\n",
		    sysnr,
		    lemona_mixers[sysnr].sysnr,
		    lemona_mixers_size);
      lemona_clients_dec();
      return (-EINVAL);
    }
  else /* lemona_mixers[sysnr].sysnr == -1 || out of bound */
    {
      lemona_printk("No mixer found for syscall: %i\n", sysnr);
      lemona_clients_dec();
      return (-EINVAL);
    }

  /* let's mix! */
  va_start(ap, extnr);
  z = lemona_zest_create(lemona_mixers + i, in, argnr, extnr, ap);
  if (IS_ERR(z))
    {
      ret		= PTR_ERR(z);
      z			= NULL;
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
		    "value than zest_get_size (syscall %i): "
		    "%i instead of %i\n",
		    sysnr, ret, z->size);
      ret = -EINVAL;
      goto out;
    }
  ret = 0;

  /*
   * TODO: call the different logging facilities:
   *  - lemona_relay_log
   *  - ...
   */
  lemona_relay_log(z);
  lemona_net_log(z);

 out:
  va_end(ap);
  kfree(z); /* it handles NULL pointer, no worries ;-) */
  lemona_clients_dec();
  return (ret);
}
