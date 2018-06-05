#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");              
MODULE_AUTHOR("Björn Daase");      
MODULE_DESCRIPTION("The first idea of wirting a FATx driver usinf the vfs interface.");  
MODULE_VERSION("0.1");             
 
static char *name = "FATxvfs";       
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");


static int fatx_fill_super(struct super_block *sb, void *data, int silent)
{
    /*struct inode *root = NULL;

    sb->s_magic = AUFS_MAGIC_NUMBER;
    sb->s_op = &aufs_super_ops;

    root = new_inode(sb);
    if (!root)
    {
         pr_err("inode allocation failed\n");
         return -ENOMEM;
    }

    root->i_ino = 0;
    root->i_sb = sb;
    root->i_atime = root->i_mtime = root->i_ctime = CURRENT_TIME;
    inode_init_owner(root, NULL, S_IFDIR);

    sb->s_root = d_make_root(root);
    if (!sb->s_root)
    {
        pr_err("root creation failed\n");
        return -ENOMEM;
    }*/

   return 0;
}

static struct dentry *fatx_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{

  printk(KERN_INFO "fatx: devname = %s\n", dev_name);
  struct dentry *entry = mount_bdev(fs_type, flags, dev_name, data, fatx_fill_super);

  if (IS_ERR(entry))
          pr_err("fat mounting failed\n");
      else
          pr_debug("fatx mounted\n");

  return entry;

}

static struct file_system_type fatx_fs_type = {
        .owner          = THIS_MODULE,
        .name           = "fatx",
        .mount          = fatx_mount,
        .kill_sb        = kill_block_super,
        .fs_flags       = FS_REQUIRES_DEV,
};

static int __init FATxvfs__init(void)
{

  printk(KERN_INFO "Hello from the FATxvfs LKM!\n");
  return register_filesystem(&fatx_fs_type);

}

static void __exit FATxvfs__exit(void)
{

  printk(KERN_INFO "Goodbye from the FATxvfs LKM!\n");
  unregister_filesystem(&fatx_fs_type);

}

module_init(FATxvfs__init);
module_exit(FATxvfs__exit);
