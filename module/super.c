
#include "super.h"
#include "fatx.h"
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/slab.h>
#include <linux/statfs.h>
#include <linux/buffer_head.h>

static void fatx_put_super(struct super_block *sb);
static int fatx_read_super(struct fatx_super_info *sbi, struct super_block *sb);
static int fatx_statfs(struct dentry *dentry, struct kstatfs *buf);

static struct super_operations const fatx_super_ops = {
    .statfs = fatx_statfs,
    .put_super = fatx_put_super,
};

static void
fatx_put_super (struct super_block *sb)
{
  struct fatx_super_info *sbi = FATX_SB(sb);

  kfree(sbi);
  sb->s_fs_info = NULL;
}

static int
fatx_read_super (struct fatx_super_info *sbi, struct super_block *sb)
{
  struct buffer_head *bh = sb_bread(sb, 0);
  if (!bh)
    return -ENOENT;

  memset(sbi, 0, sizeof(*sbi));

  memcpy(&(sbi->manufacturer_description), bh->b_data + 3, 8);

  return 0;
}

static int
fatx_statfs(struct dentry *dentry, struct kstatfs *buf)
{
  struct super_block *sb = dentry->d_sb;

  buf->f_type = FATX_MAGIC_NUMBER;
  buf->f_bsize = sb->s_blocksize;

  return 0;
}

int
fatx_fill_super (struct super_block *sb, void *data, int silent)
{
  int res;
  struct fatx_super_info *sbi = NULL;

  sbi = kzalloc(sizeof(*sbi), GFP_KERNEL);
  if (!sbi)
    return -ENOMEM;
  sb->s_fs_info = sbi;

  if (0 != (res = fatx_read_super(sbi, sb)))
    {
      kfree(sbi);
      return res;
    }

  sb->s_flags |= SB_NODIRATIME;
  sb->s_magic = FATX_MAGIC_NUMBER;
  sb->s_op = &fatx_super_ops;

  // conjure up a temporary root inode (required for mounting)
  struct inode *root = new_inode(sb);
  root->i_mode = 0755 | S_IFDIR;
  sb->s_root = d_make_root(root);

  return 0;
}

