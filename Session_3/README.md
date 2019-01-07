
@Date : 21/12/2018
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-3
/*********************************************************************************************/
1.statically & Dynamically Allocating Major and Minor Number

File : Hello_World.c
File : Devicefile.c
Description :
                This file is a simple Hello World module.Contains basic module_init and module_exit functions 
		And for register and unregister major & minor number.
		
		The automatic creation of device files can be handled with udev. 
		Udev is the device manager for the Linux kernel that creates/removes device nodes in the /dev directory dynamically.

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod Hello_World.ko
3.See the added module          cat /proc/devices | grep "Spanidea"
4.See the logs in dmesg         dmesg | tail -10
  kernel ring buffer
5.Remove module                 sudo rmmod Hello_World
6.Run                           make clean


Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod Devicefile.ko
3.See the added module          ls -l /dev/ | grep ext_device
4.See the logs in dmesg         dmesg 
  kernel ring buffer
5.Remove module                 sudo rmmod Devicefile
6.Run                           make clean


Keypoints to remember:
1.static int Hello_World_init();
2.void Hello_World_exit();
3.module_init();
4.module_exit();
5.int register_chrdev_region(dev_t first, unsigned int count, char *name);

	-> Here, first is the beginning device number of the range you would like to allocate.

	-> count is the total number of contiguous device numbers you are requesting. 
	   Note that, if count is large, the range you request could spill over to the next major number; 
	   but everything will still work properly as long as the number range you request is available.

	-> name is the name of the device that should be associated with this number range; 
	   it will appear in /proc/devices and sysfs.

	-> The return value from register_chrdev_region will be 0 if the allocation was successfully performed. 
	   In case of error, a negative error code will be returned, and you will not have access to the requested region.
6.void unregister_chrdev_region(dev_t first, unsigned int count);

7.int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);

	-> dev is an output-only parameter that will, on successful completion, hold the first number in your allocated range.

	-> firstminor should be the requested first minor number to use; it is usually 0.

	-> count is the total number of contiguous device numbers you are requesting.

	-> name is the name of the device that should be associated with this number range; it will appear in /proc/devices and sysfs.
	



Keypoints to remember:
1.static int Hello_World_init();
2.void Hello_World_exit();
3.module_init();
4.module_exit();
5.int register_chrdev_region(dev_t first, unsigned int count, char *name);

	-> Here, first is the beginning device number of the range you would like to allocate.

	-> count is the total number of contiguous device numbers you are requesting. 
	   Note that, if count is large, the range you request could spill over to the next major number; 
	   but everything will still work properly as long as the number range you request is available.

	-> name is the name of the device that should be associated with this number range; 
	   it will appear in /proc/devices and sysfs.

	-> The return value from register_chrdev_region will be 0 if the allocation was successfully performed. 
	   In case of error, a negative error code will be returned, and you will not have access to the requested region.
6.void unregister_chrdev_region(dev_t first, unsigned int count);

7.int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);

	-> dev is an output-only parameter that will, on successful completion, hold the first number in your allocated range.

	-> firstminor should be the requested first minor number to use; it is usually 0.

	-> count is the total number of contiguous device numbers you are requesting.

	-> name is the name of the device that should be associated with this number range; it will appear in /proc/devices and sysfs.
	


