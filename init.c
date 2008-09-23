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

struct lemona*		juice = NULL;

static void		lemona_cleanup(void)
{
  lemona_relay_cleanup();
  if (juice)
    kfree(juice);
}

static int __init	lemona_init(void)
{
  long			err = 0;

  printk("Initialization Lemona for kernel tree " UTS_RELEASE "...");
  juice = kzalloc(sizeof(*juice), GFP_KERNEL);
  if (juice == NULL)
    {
      err = -ENOMEM;
      goto err;
    }
  err = lemona_relay_init();
  if (err)
    goto err;
  printk("Done\n");
  return (0);

 err:
  lemona_cleanup();
  printk("Failed\n");
  return (err);
}

static void __exit	lemona_exit(void)
{
  printk("Uninitializing Lemona...");
  lemona_cleanup();
  printk("Done\n");
}

module_init(lemona_init);
module_exit(lemona_exit);
