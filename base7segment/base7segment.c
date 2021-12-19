#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <asm/uaccess.h>

#define DRIVER_AUTHOR	"SKKU"
#define DRIVER_DESC	"Base Board 7-Segment program"
#define SEGMENT_NAME "base7segment"
#define SEGMENT_MODULE_VERSION "BASE7SEG V1.0"

unsigned int ibuf[8];

static int base7segment_open(struct inode * inode, struct file * file){
	int err, i;
	
	printk("base7segment_open, \n");
	gpio_free(EXYNOS4_GPC0(0));
	gpio_free(EXYNOS4_GPC0(1));
	for(i=0; i<8; i++)
		gpio_free(EXYNOS4_GPL0(i));

	err = gpio_request(EXYNOS4_GPC0(0), "GPC0(0)");
	if (err) {
		printk("#### base7segment.c failed to request GPC0(0)\n");
		return err;
	}
	s3c_gpio_setpull(EXYNOS4_GPC0(0), S3C_GPIO_PULL_UP);
	gpio_direction_output(EXYNOS4_GPC0(0), 1);

	err = gpio_request(EXYNOS4_GPC0(1), "GOC0(1)");
	if (err) {
		printk("#### base7segment.c failed to request GPC0(1)\n");
		return err;
	}
	s3c_gpio_setpull(EXYNOS4_GPC0(1), S3C_GPIO_PULL_UP);
	gpio_direction_output(EXYNOS4_GPC0(1), 1);
	
	for(i=0; i<8; i++) {
		err = gpio_request(EXYNOS4_GPL0(i), "Segment");
		if (err) {
			printk("#### base7segment.c failed to request GPL0(%d) errno %d\n", i, err);
			return err;
		}
		s3c_gpio_setpull(EXYNOS4_GPL0(i), S3C_GPIO_PULL_NONE);
		gpio_direction_output(EXYNOS4_GPL0(i), 0);
	}
	return 0;
}

static int base7segment_release(struct inode * inode, struct file * file){
	int i;
	printk("base7segment_release, \n");
	
	gpio_free(EXYNOS4_GPC0(0));
	gpio_free(EXYNOS4_GPC0(1));
	for (i=0; i<8; i++)
		gpio_free(EXYNOS4_GPL0(i));

	return 0;
}

int Getsegmentcode_base (int x) {
	unsigned int i;

	printk("Getsegmentcode_base input %d \n", x);
	for (i=0; i<8; i++)
		ibuf[i] = 0;

	switch (x)
	{
	case 0:
		for (i=0; i<6; i++)
			ibuf[i] = 1;
		break;
	case 1:
		ibuf[1] = 1;
		ibuf[2] = 1;
		break;
	case 2:
		for (i=0; i<2; i++)
			ibuf[i] = 1;
		for (i= 3; i<5; i++)
			ibuf[i] = 1;
		ibuf[6] = 1;
		break;
	case 3:
		for (i= 0; i<4; i++)
			ibuf[i] = 1;
		ibuf[6] = 1;
		break;
	case 4:
		for (i=1; i<3; i++)
			ibuf[i] = 1;
		for (i= 5; i<7; i++)
			ibuf[i] = 1;
		break;
	case 5:
		ibuf[0] = 1;
		for (i=2; i<4; i++)
			ibuf[i] = 1;
		for (i= 5; i<7; i++)
			ibuf[i] = 1;
		break;
	case 6:
		ibuf[0] = 1;
		for (i=2; i<7; i++)
			ibuf[i] = 1;
		break;
	case 7:
		for (i=0; i<3; i++)
			ibuf[i] = 1;
		ibuf[5] = 1;
		break;
	case 8:
		for (i=0; i<7; i++)
			ibuf[i] = 1;
		break;
	case 9:
		for (i=0; i<4; i++)
			ibuf[i] = 1;
		for (i= 5; i<7; i++)
			ibuf[i] = 1;
		break;
	case 10:
		for (i=0; i<3; i++)
			ibuf[i] = 1;
		for (i= 4; i<8; i++) /* 7? */
			ibuf[i] = 1;
		break;
	case 11:
		for (i=0; i<8; i++)
			ibuf[i] = 1;
		break;
	case 12:
		for (i=3; i<6; i++)
			ibuf[i] = 1;
		ibuf[0] = 1;
		ibuf[7] = 1;
		break;
	case 13:
		ibuf[7] = 1;
		for (i= 0; i<6; i++)
			ibuf[i] = 1;
		break;
	case 14:
		for (i=3; i<8; i++)
			ibuf[i] = 1;
		ibuf[0] = 1;
		break;
	case 15:
		for (i=4; i<8; i++)
			ibuf[i] = 1;
		ibuf[0] = 1;
		break;
	default:
		for (i=0; i<8; i++)
			ibuf[i] = 1;
		break;
	}

	return 0;
}

static ssize_t base7segment_write(struct file * file, const char * buf, size_t length, loff_t * ofs){
	unsigned int ret, i;
	unsigned char data[2];

	printk("base7segment_write, \n");
	ret = copy_from_user(data, buf, 2);

 	Getsegmentcode_base((unsigned int) data[0]);
	gpio_direction_output(EXYNOS4_GPC0(0), 0);
	gpio_direction_output(EXYNOS4_GPC0(1), 1);
	for (i=0; i<8; i++) {
		gpio_direction_output(EXYNOS4_GPL0(i), (unsigned int)ibuf[i]);
	}
	mdelay(2000);

	Getsegmentcode_base((unsigned int) data[1]);
	gpio_direction_output(EXYNOS4_GPC0(0), 1);
	gpio_direction_output(EXYNOS4_GPC0(1), 0);
	for (i=0; i<8; i++) {
		gpio_direction_output(EXYNOS4_GPL0(i), (unsigned int)ibuf[i]);
	}
	mdelay(1);

	return 0;
}

static struct file_operations base7segment_fops = {
	.owner = THIS_MODULE,
	.open = base7segment_open,
	.release = base7segment_release,
	//.read = base7segment_read,
	.write = base7segment_write,
	//.unlocked_ioctl = base7segment_ioctl,
};

static struct miscdevice base7segment_driver = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = SEGMENT_NAME,
	.fops = &base7segment_fops,
};

static int base7segment_init(void){
	printk("base7segment_init, \n");
	
	return misc_register(&base7segment_driver);
}

static void base7segment_exit(void){
	printk("base7segment_exit, \n");

	misc_deregister(&base7segment_driver);
	
}

module_init(base7segment_init);
module_exit(base7segment_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("Dual BSD/GPL");
