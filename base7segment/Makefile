.SILENT:

include C:/AndroXStudio/Tools/make_adb

export ARCH=arm
export CROSS_COMPILE=arm-linux-androideabi-

ifneq ($(KERNELRELEASE),)
obj-m := base7segment.o
else
KDIR := /platform/linux
all:
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules

	echo 
	echo "**** Install:" /system/lib/modules/base7segment.ko "****"
	$(ADB) push base7segment.ko /system/lib/modules/
	$(ADB) shell chmod 644 /system/lib/modules/base7segment.ko
	echo 
	echo "**** Load Module:" /system/lib/modules/base7segment.ko "****"
	$(ADB) shell toolbox rmmod base7segment > /dev/null
	$(ADB) shell insmod /system/lib/modules/base7segment.ko
	$(ADB) shell lsmod | grep base7segment
	echo

endif

clean:
	rm -f *.symvers
	rm -f *.ko
	rm -f *.o
	rm -f *.mod.c
	rm -f *.order
	rm -f .*.cmd
	rm -rf .tmp_versions
