.SILENT:

include C:/AndroXStudio/Tools/make_adb

export ARCH=arm
export CROSS_COMPILE=arm-linux-androideabi-

ifneq ($(KERNELRELEASE),)
obj-m := lhg_fpgaPiezo_driver.o
else
KDIR := /platform/linux
all:
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules

	echo 
	echo "**** Install:" /system/lib/modules/lhg_fpgaPiezo_driver.ko "****"
	$(ADB) push lhg_fpgaPiezo_driver.ko /system/lib/modules/
	$(ADB) shell chmod 644 /system/lib/modules/lhg_fpgaPiezo_driver.ko
	echo 
	echo "**** Load Module:" /system/lib/modules/lhg_fpgaPiezo_driver.ko "****"
	$(ADB) shell toolbox rmmod lhg_fpgaPiezo_driver > /dev/null
	$(ADB) shell insmod /system/lib/modules/lhg_fpgaPiezo_driver.ko
	$(ADB) shell lsmod | grep lhg_fpgaPiezo_driver
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
