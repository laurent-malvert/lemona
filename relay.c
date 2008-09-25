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

#include <linux/module.h> /* module_param */

#include <linux/relay.h>
#include <linux/debugfs.h>

#include "lemona.h"

/*
 * Lemona module's options
 */
static char		*debugfs_dir_name = CONFIG_LEMONA_DEBUGFS_DIR;
module_param(debugfs_dir_name, charp, S_IRUGO);
/***/

extern struct lemona	*juice;

static struct dentry	*lemona_relay_create_buf_file(const char *filename,
						      struct dentry *parent,
						      int mode,
						      struct rchan_buf *buf,
						      int *is_global)
{
  return (debugfs_create_file(filename, mode, parent,
			      buf, &relay_file_operations));
}

static int		lemona_relay_remove_buf_file(struct dentry *dentry)
{
  debugfs_remove(dentry);
  return (0);
}

static struct rchan_callbacks	relay_callbacks = {
  .create_buf_file	= lemona_relay_create_buf_file,
  .remove_buf_file	= lemona_relay_remove_buf_file
};

int __init		lemona_relay_init(void)
{
  long			err = 0;

  if (juice)
    {
      juice->dfs_dir = debugfs_create_dir(debugfs_dir_name, NULL);
      if (juice->dfs_dir == NULL)
	{
	  lemona_printk("debugfs_create_dir: failed\n");
	  err = IS_ERR(juice->dfs_dir) ? PTR_ERR(juice->dfs_dir) : -ENOMEM;
	  goto err;
	}
      juice->rchan = relay_open(LEMONA_RELAY_CHANNEL_NAME, juice->dfs_dir,
				512 * 1024, 5, &relay_callbacks, NULL);
      if (juice->rchan == NULL)
	{
	  lemona_printk("relay_open: failed\n");
	  err = IS_ERR(juice->rchan) ? PTR_ERR(juice->rchan) : -ENOMEM;
	  goto err;
	}
    }
  return (err);

 err:
  lemona_relay_cleanup();
  return (err);
}

int			lemona_relay_log(struct zest *zest)
{
  // TODO: implement lemona_relay_log
  return (-ENOSYS);
}

void			lemona_relay_cleanup(void)
{
  if (juice)
    {
      if (juice->relay.chan)
	relay_close(juice->relay.chan);
      if (juice->relay.dir)
	debugfs_remove(juice->relay.dir);
    }
}
