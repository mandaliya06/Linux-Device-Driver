/************************************************************************************************
@fileName : My_SysFs.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is a module for System File System(SysFS) Entry.
@license  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/************************************************************************************************
                        		INCLUDES
************************************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sysfs.h>    //sysfs
#include <linux/kobject.h>  //sysfs
/**********************************************************************************************
                         		LOCAL MACROS           
**********************************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "KISHAN MANDALIYA"
#define DRIVER_MODULE_DESC                      "SysFs"
#define DRIVER_MODULE_VERSION                   "V1.7"
#define SUCCESS  0
#define FAILURE -1
#define STATIC_METHOD 0

/***********************************************************************************************
                         		LOCAL TYPEDEFS         
***********************************************************************************************/

/**********************************************************************************************
                        		GLOBAL VARIABLES                
**********************************************************************************************/
volatile int My_value = 0;
dev_t dev = 0;
static struct class *dev_class;
static struct cdev My_cdev;
struct kobject *kobj_ref;

/*********************************************************************************************
                        		LOCAL VARIABLES         
*********************************************************************************************/

/********************************************************************************************
                        		LOCAL FUNCTIONS         
********************************************************************************************/
static int  My_Driver_init(void);
static void My_Driver_exit(void);

/***************************************Driver Functions*************************************/
static int My_open(struct inode *inode, struct file *file);
static int My_release(struct inode *inode, struct file *file);
static ssize_t My_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t My_write(struct file *filp, const char *buf, size_t len, loff_t *off);

/*******************************************SysFs Function*******************************************/
static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t sysfs_store(struct kobject *kobj,struct kobj_attribute *attr,const char *buf, size_t count);

struct kobj_attribute My_attr = __ATTR(My_value, 0660, sysfs_show, sysfs_store);

static struct file_operations fops =
{
	.owner		= THIS_MODULE,
	.read		= My_read,
	.write		= My_write,
	.open		= My_open,
	.release	= My_release,
};


static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	printk(KERN_INFO "SysFs.......Read!!!\n");
	return sprintf(buf,"%d", My_value);
}

static ssize_t sysfs_store(struct kobject *kobj,struct kobj_attribute *attr,const char *buf, size_t count)
{
	printk(KERN_INFO "SysFs.......Write!!!\n");
	sscanf(buf,"%d",&My_value);
	return count;
}

static int My_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Device File Opened...!!!\n");
	return SUCCESS;
}
static int My_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Device File Closed...!!!\n");
	return SUCCESS;
}
static ssize_t My_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "My Read Function...!!!\n");
	return SUCCESS;
}
static ssize_t My_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "My Read Function...!!!\n");
	return SUCCESS;
}
/*********************************************************************************************
function         : My_Driver_init
description      : This function is initialised when module gets inserted.
                   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static int My_Driver_init(void) 
{
    if(STATIC_METHOD)
    {
    	 register_chrdev_region(dev, 1, "My_dev"); //statically Allocating major number
    }
    else
    {
    	if((alloc_chrdev_region(&dev, 0, 1, "My_dev"))<0){
		printk(KERN_INFO "Cannot allocate major numer for devices \n");
		return FAILURE;
    	}
    }
    printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
    
    /* Creating cdev structure*/
    cdev_init(&My_cdev,&fops);
    
    /* Adding character device to the system */
    if((cdev_add(&My_cdev, dev, 1)) < 0){
   	printk(KERN_INFO "Can't add the device to the sytem \n");
	goto r_class;
    }

   /* Creating struct class */
   if((dev_class = class_create(THIS_MODULE,"My_class")) == NULL){
	printk(KERN_INFO "Can't create the struct class");
	goto r_class;
    }
    /* Creating Device */
    if((device_create(dev_class, NULL, dev, NULL, "My_device")) == NULL){
	printk(KERN_INFO "Can't create the Device 1 \n");
	goto r_device;
    }
    /* Creating a directory in /sys/kernel/ */
    kobj_ref = kobject_create_and_add("My_sysfs", kernel_kobj);

    /* Creating sysfs file for My_value */
    if(sysfs_create_file(kobj_ref, &My_attr.attr)){
		printk(KERN_INFO "cannot create sysfs file.....\n");
		goto r_sysfs;
    }
    	printk(KERN_INFO "My Driver Insert...Done!!! \n");
    return SUCCESS;

r_sysfs:
	kobject_put(kobj_ref);
	sysfs_remove_file(kernel_kobj,&My_attr.attr);

r_device : 
	class_destroy(dev_class);
r_class :
	unregister_chrdev_region(dev, 1);
	cdev_del(&My_cdev);
	return FAILURE;
}

/**********************************************************************************************
function         : My_Driver_exit
description      : This function is initialised when module gets removed.
                   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static void My_Driver_exit(void) 
{
    kobject_put(kobj_ref);
    sysfs_remove_file(kernel_kobj, &My_attr.attr);
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&My_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "My Driver Remove...Done!!!\n");
}

module_init(My_Driver_init);
module_exit(My_Driver_exit);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);


