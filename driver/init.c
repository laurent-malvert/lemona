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

#include <linux/init.h>		/* module_* */
#include <linux/module.h>	/* MODULE_LICENSE */
#include <linux/utsrelease.h>	/* UTS_RELEASE */

#include <linux/relay.h>	/* relay */
#include <linux/debugfs.h>	/* debugfs */

#include "lemona.h"

MODULE_LICENSE("Dual MIT/GPL");

extern atomic_t		lemona_activated;
extern atomic_t		lemona_clients;

struct lemona*		juice			= NULL;

static void		lemona_cleanup(void)
{
  lemona_relay_cleanup();
  if (juice)
    kfree(juice);
}

static int __init	lemona_init(void)
{
  long			err = 0;

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
  lemona_printk("Done.\n");
  atomic_set(&lemona_activated, 1);
  return (0);

 err:
  lemona_cleanup();
  lemona_printk("Failed.\n");
  return (err);
}

static void __exit	lemona_exit(void)
{
  lemona_printk("Uninitializing Lemona...\n");
  atomic_set(&lemona_activated, 0);
  /*
   * Wait until our last client finish working.
   * Their logs will be lost anyway, but we don't want to generate an Oops
   */
  if (atomic_read(&lemona_clients) > 0)
    schedule();
  lemona_cleanup();
  lemona_printk("Done.\n");
}

module_init(lemona_init);
module_exit(lemona_exit);