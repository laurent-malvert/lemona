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

#include "lemona.h"

/*
 * Lemona module's options
 */
static char		*debugfs_dir_name	= CONFIG_LEMONA_DEBUGFS_DIR;
static int		relay_subbuf_sz		= CONFIG_LEMONA_RELAY_SBUF_SZ;
static int		relay_subbuf_nr		= CONFIG_LEMONA_RELAY_SBUF_NR;
module_param(debugfs_dir_name, charp, S_IRUGO);
module_param(relay_subbuf_sz, int, S_IRUGO);
module_param(relay_subbuf_nr, int, S_IRUGO);
/***/

extern struct lemona	*juice;

/*
 * For now, I've decided to put ourselves in no-overwrite mode. I
 * frankly don't know which one to choose. Is it more important to
 * have the following zest or the one already written? Hard choice,
 * he?
 */
static int		lemona_relay_subbuf_start(struct rchan_buf *buf,
						  void *subbuf,
						  void *prev_subbuf,
						  unsigned int prev_padding)
{
  if (relay_buf_full(buf))
    return (0); /* TODO: some code to avoid creating zest if it's full */
  return (1);
}

static struct dentry	*lemona_relay_create_buf_file(const char *filename,
						      struct dentry *parent,
						      int mode,
						      struct rchan_buf *buf,
						      int *is_global)
{
  struct dentry			*d;
  struct lemona_relay_file	*f;

  d = debugfs_create_file(filename, mode, parent,
			  buf, &relay_file_operations);
  if (d != NULL)
    {
      f = kmalloc(sizeof(*f), GFP_KERNEL);
      if (f == NULL)
	{
	  debugfs_remove(d);
	  d = NULL;
	}
      else
	{
	  f->d = d;
	  list_add_tail(&(f->next), &(juice->relay.files));
	}
    }
  return (d);
}

static int		lemona_relay_remove_buf_file(struct dentry *dentry)
{
  struct lemona_relay_file	*f;

  list_for_each_entry(f, &(juice->relay.files), next) {
    if (f->d == dentry)
      {
	list_del(&(f->next));
	kfree(f);
	break;
      }
  }
  debugfs_remove(dentry);
  return (0);
}

static struct rchan_callbacks	relay_callbacks = {
  .subbuf_start		= lemona_relay_subbuf_start,
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
      /*
	need to be done before relay_open, since relay open will call
	our lemona_relay_subbuf_start handler which use the list
      */
      INIT_LIST_HEAD(&(juice->relay.files));
      juice->rchan = relay_open(LEMONA_RELAY_CHANNEL_NAME, juice->dfs_dir,
				relay_subbuf_sz, relay_subbuf_nr,
				&relay_callbacks, NULL);
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

bool			__lemona_relay_is_ours(const struct dentry *dentry)
{
  struct lemona_relay_file	*f;

  list_for_each_entry(f, &(juice->relay.files), next) {
    if (f->d == dentry)
      return (true);
  }
  return (false);
}

void			lemona_relay_log(const struct lemona_zest *zest)
{
  /* Zest are aligned on sizeof(int) */
  relay_write(juice->rchan, zest,
	      (zest->size / sizeof(int)
	       + zest->size % sizeof(int)) * sizeof(int));
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
