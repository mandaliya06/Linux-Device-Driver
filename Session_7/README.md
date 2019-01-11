
@Date : 10/1/2019
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-7
/*********************************************************************************************/
1.Process File System

File : My_SysFs.c

Description :
               This file is which create System file in /sys dir and read and write from that sys file variables file. 
		

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod My_SysFs.ko
  kernel ring buffer
3.see the sysfs entry in 
/sys/kernel directroy 		cat /sys/kernel/My_SysFs/My_value
4. write in My_proc             echo 1234 > /sys/kernel/My_sysFs/My_value
5.Remove module                 sudo rmmod My_SysFs
6.Run                           make clean

Key points :

->  We can create attribute using __ATTR macro __ATTR(name, permission, show_ptr, store_ptr);
->  kobj_ref = kobject_create_and_add("etx_sysfs",kernel_kobj);
->  int sysfs_create_file ( struct kobject *  kobj, const struct attribute * attr);
->  ssize_t (*show)(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
->  ssize_t (*store)(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);






