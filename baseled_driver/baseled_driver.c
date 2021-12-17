#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>

#define DRIVER_AUTHOR "hanback"
#define DRIVER_DESC "BaseLed program"
#define BASELED_NAME "baseled"
#define BASELED_MODULE_VERSION "BASE LED V1.0"

static int baseled_driver_open(struct inode * inode, struct file * file){
	int err, i;

	printk("baseled_driver_open, \n");
	
	for (i=0; i<7; i++) {
		err = gpio_request(EXYNOS4_GPK0(i), "BaseLed");
		if (err)
			printk("baseled.c failed to reuest GPK0(%d) \n", i);

		s3c_gpio_setpull(EXYNOS4_GPK0(i), S3C_GPIO_PULL_NONE);
		gpio_direction_output(EXYNOS4_GPK0(i), 0);
	}

	err = gpio_request(EXYNOS4_GPC1(2), "GPC1(2)");
	if (err)
		printk("#### baseled.c failed to reuest GPC1(2) #### \n");

	s3c_gpio_setpull(EXYNOS4_GPC1(2), S3C_GPIO_PULL_NONE);
	gpio_direction_output(EXYNOS4_GPC1(2), 0);

	return 0;
}

static int baseled_driver_release(struct inode *minode, struct file *mfile){
	int i;

	printk("baseled_driver_release \n");
	for (i=0; i<7; i++)
		gpio_free(EXYNOS4_GPK0(i));
	
	gpio_free(EXYNOS4_GPC1(2));
	return 0;
}

static ssize_t baseled_driver_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what){
	int ret;
	unsigned char buf[8];

	printk("baseled_driver_write, \n");

	ret = copy_from_user(buf, gdata, length);
	gpio_direction_output(EXYNOS4_GPK0(0), (unsigned int) buf[0]);
	gpio_direction_output(EXYNOS4_GPK0(1), (unsigned int) buf[1]);
	gpio_direction_output(EXYNOS4_GPK0(2), (unsigned int) buf[2]);
	gpio_direction_output(EXYNOS4_GPK0(3), (unsigned int) buf[3]);
	gpio_direction_output(EXYNOS4_GPK0(4), (unsigned int) buf[4]);
	gpio_direction_output(EXYNOS4_GPK0(5), (unsigned int) buf[5]);
	gpio_direction_output(EXYNOS4_GPK0(6), (unsigned int) buf[6]);
	gpio_direction_output(EXYNOS4_GPC1(2), (unsigned int) buf[7]);

	return length;
}

static struct file_operations baseled_driver_fops = {
	.owner = THIS_MODULE,
	.open = baseled_driver_open,
	.release = baseled_driver_release,
	.write = baseled_driver_write,
	//.unlocked_ioctl = baseled_driver_ioctl,
};

static struct miscdevice baseled_driver_driver = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = BASELED_NAME,
	.fops = &baseled_driver_fops,
};

static int baseled_driver_init(void){
	printk("baseled_driver_init, \n");
	
	return misc_register(&baseled_driver_driver);
}

static void baseled_driver_exit(void){
	printk("baseled_driver_exit, \n");

	misc_deregister(&baseled_driver_driver);
	
}

module_init(baseled_driver_init);
module_exit(baseled_driver_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("Dual BSD/GPL");
