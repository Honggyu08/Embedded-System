#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/ioport.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>

#define PIEZO_ADDRESS			0x05000050
#define PIEZO_ADDRESS_RANGE 	0x1000

#define DEVICE_NAME			"lhg_fpgaPiezo_driver"

static int piezo_usage = 0;
static unsigned long int *piezo_ioremap;
static unsigned char *piezo_addr;

static int lhg_fpgaPiezo_driver_open(struct inode * inode, struct file * file)
{
	if (piezo_usage == -1)
		return -EBUSY;

	piezo_ioremap = ioremap(PIEZO_ADDRESS, PIEZO_ADDRESS_RANGE);

	if ( check_mem_region( (unsigned long int) piezo_ioremap, PIEZO_ADDRESS_RANGE) /* != 0 */)
	{
		printk(KERN_WARNING "Can't get IO Region 0x%x\n", (unsigned int) piezo_ioremap);
		return -1;
	}
	
	request_mem_region( (unsigned long int) piezo_ioremap, PIEZO_ADDRESS_RANGE, DEVICE_NAME);
	piezo_addr = (unsigned char *)piezo_ioremap;
	piezo_usage = 1;

	return 0;
}

static int lhg_fpgaPiezo_driver_release(struct inode * inode, struct file * file)
{
	release_mem_region( (unsigned long int) piezo_ioremap, PIEZO_ADDRESS_RANGE);
	iounmap(piezo_ioremap);

	piezo_usage = 0;
	return 0;
}

/* not use
static ssize_t lhg_fpgaPiezo_driver_read(struct file * file, char * buf, size_t length, loff_t * ofs)
{
	printk("lhg_fpgaPiezo_driver_read, \n");
	
	return 0;
}
*/

static ssize_t lhg_fpgaPiezo_driver_write(struct file * file, const char * buf, size_t length, loff_t * ofs)
{
	unsigned char c;

	get_user(c, buf);

	*piezo_addr = c;
	
	return length;
}

/* not use
static DEFINE_MUTEX(lhg_fpgaPiezo_driver_mutex);
static long lhg_fpgaPiezo_driver_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
	printk("lhg_fpgaPiezo_driver_ioctl, \n");
	
	switch(cmd){
		default:
			mutex_unlock(&lhg_fpgaPiezo_driver_mutex);
			return ENOTTY;
	}
	
	mutex_unlock(&lhg_fpgaPiezo_driver_mutex);
	return 0;
}
*/

static struct file_operations lhg_fpgaPiezo_driver_fops = {
	.owner = THIS_MODULE,
	.open = lhg_fpgaPiezo_driver_open,
	.release = lhg_fpgaPiezo_driver_release,
//	.read = lhg_fpgaPiezo_driver_read,
	.write = lhg_fpgaPiezo_driver_write,
//	.unlocked_ioctl = lhg_fpgaPiezo_driver_ioctl,
};

static struct miscdevice lhg_fpgaPiezo_driver = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "lhg_fpgaPiezo_driver",
	.fops = &lhg_fpgaPiezo_driver_fops,
};

static int lhg_fpgaPiezo_driver_init(void){
	printk("lhg_fpgaPiezo_driver_init, \n");
	
	return misc_register(&lhg_fpgaPiezo_driver);
}

static void lhg_fpgaPiezo_driver_exit(void){
	printk("lhg_fpgaPiezo_driver_exit, \n");

	misc_deregister(&lhg_fpgaPiezo_driver);
	
}

module_init(lhg_fpgaPiezo_driver_init);
module_exit(lhg_fpgaPiezo_driver_exit);

MODULE_AUTHOR("SKKU_LHG");
MODULE_DESCRIPTION("lhg_fpgaPiezo_driver");
MODULE_LICENSE("Dual BSD/GPL");
