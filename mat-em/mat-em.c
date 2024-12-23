#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>


#define DEVICE_NAME	"mat-em"
char bitstream[129];

static ssize_t MyRead(struct file *filp, char *buffer, size_t count, loff_t *f_pos)
{
	size_t len;
	int ret;
        len = 129;
	ret = copy_to_user(buffer, bitstream, len);
        printk("My read invoked");
	
  	if (*f_pos == 0) {
    		*f_pos+=len;
    		return len;
  	} else {
    		return 0;
 	}
}

static ssize_t MyWrite (struct file *filp, const char * buffer, size_t count, loff_t *f_pos) {
	int ret;
        printk("My Write invoked");
	ret = copy_from_user(&bitstream,buffer,count);
	*f_pos+=count;
	printk("%s",bitstream); 
	if (bitstream[count-1]!= '\n') printk("\n");
	return count;
}

static struct file_operations dev_fops = {
	owner:		THIS_MODULE,
	read:		MyRead,
	write:		MyWrite,	
};

static struct miscdevice misc = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= DEVICE_NAME,
	.fops	= &dev_fops,
};

static int __init dev_init(void)
{
	int ret;

	ret = misc_register(&misc);
	printk (DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit dev_exit(void)
{
	printk (DEVICE_NAME"\tremoved\n");
misc_deregister(&misc);
}
module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GP");
MODULE_AUTHOR("Ayesha Babar");
