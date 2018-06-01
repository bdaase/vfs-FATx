#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");              
MODULE_AUTHOR("Björn Daase");      
MODULE_DESCRIPTION("The first idea of wirting a FATx driver usinf the vfs interface.");  
MODULE_VERSION("0.1");             
 
static char *name = "FATxvfs";       
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");


static int __init FATxvfs__init(void){

   printk(KERN_INFO "Hello from the FATxvfs LKM!\n");
   return 0;

}

static void __exit FATxvfs__exit(void){

   printk(KERN_INFO "Goodbye from the FATxvfs LKM!\n");

}

module_init(FATxvfs__init);
module_exit(FATxvfs__exit);
