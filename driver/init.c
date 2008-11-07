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

#include <linux/sched.h>	/* schedule */
#include <linux/init.h>		/* module_* */
#include <linux/module.h>	/* MODULE_LICENSE */
#include <linux/utsrelease.h>	/* UTS_RELEASE */

#include "lemona.h"

MODULE_LICENSE("Dual MIT/GPL");

#if defined(CONFIG_LEMONA_MODULE)
extern atomic_t			lemona_clients;
# define lemona_clients_wait()			\
  while (atomic_read(&lemona_clients) > 0)	\
    schedule();
#else
# define lemona_clients_wait()
#endif

struct lemona			*juice			= NULL;

static void				lemona_cleanup(void)
{
  lemona_relay_cleanup();
  lemona_net_cleanup();
  if (juice)
    kfree(juice);
  juice = NULL;
}

static int __init		lemona_init(void)
{
  long				err = 0;
  extern atomic_t		lemona_activated;

  lemona_printk("Initialization for kernel tree " UTS_RELEASE "...\n");
  juice = kzalloc(sizeof(*juice), GFP_KERNEL);
  if (juice == NULL)
    {
      err = -ENOMEM;
      goto err;
    }
  err = lemona_relay_init();
  if (err)
    goto err;
  err = lemona_net_init(true);
  if (err < 0)
    goto err;

  lemona_printk("Done.\n");
  atomic_set(&lemona_activated, 1);
  return (0);

 err:
  lemona_cleanup();
  lemona_printk("Failed.\n");
  return (err);
}

static void __exit		lemona_exit(void)
{
  extern atomic_t		lemona_activated;

  lemona_printk("Uninitializing Lemona...\n");
  atomic_set(&lemona_activated, 0);
  /*
   * Wait until our last client finish working.
   * Their logs will be lost anyway, but we don't want to generate an Oops
   */
  lemona_clients_wait();
  lemona_cleanup();
  lemona_printk("Done.\n");
}

module_init(lemona_init);
module_exit(lemona_exit);
