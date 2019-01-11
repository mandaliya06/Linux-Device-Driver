/************************************************************************************************
@fileName : My_IOCTL.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is a module for Input/Output Control(IOCTL) Command.
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
#include <linux/ioctl.h>

/**********************************************************************************************
                         		LOCAL MACROS           
**********************************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "KISHAN MANDALIYA"
#define DRIVER_MODULE_DESC                      "Input/Output control"
#define DRIVER_MODULE_VERSION                   "V1.5"
#define SUCCESS  0
#define FAILURE -1
#define STATIC_METHOD 0

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
/***********************************************************************************************
                         		LOCAL TYPEDEFS         
***********************************************************************************************/

/**********************************************************************************************
                        		GLOBAL VARIABLES                
**********************************************************************************************/
dev_t dev = 0;
int32_t value = 0;
static struct class *dev_class;
static struct cdev My_cdev;
/*********************************************************************************************
                        		LOCAL VARIABLES         
*********************************************************************************************/

/********************************************************************************************
                        		LOCAL FUNCTIONS         
********************************************************************************************/
static int My_Driver_init(void);
static void My_Driver_exit(void);

static int My_open(struct inode *inode, struct file *file);
static int My_release(struct inode *inode, struct file *file);

static ssize_t My_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t My_write(struct file *filp, const char *buf, size_t len, loff_t *off);

static long My_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops =
{
	.owner		= THIS_MODULE,
	.read		= My_read,
	.write		= My_write,
	.open		= My_open,
	.unlocked_ioctl = My_ioctl,
	.release	= My_release,
};

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

static long My_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

	switch(cmd){
		case WR_VALUE :
			copy_from_user(&value, (int32_t*) arg, sizeof(value));
			printk(KERN_INFO "Value = %d\n",value);
			break;
		case RD_VALUE :
			copy_to_user((int32_t*) arg, &value, sizeof(value));
			break;
	}
	return SUCCESS;
}
/**********************************************************************************************
function         : Hello_World_init
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
    printk(KERN_INFO "My Driver Insert...Done!!! \n");
    return SUCCESS;

r_device : 
	class_destroy(dev_class);
r_class :
	unregister_chrdev_region(dev, 1);
	return FAILURE;
}

/**********************************************************************************************
function         : Hello_World_exit
description      : This function is initialised when module gets removed.
                   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static void My_Driver_exit(void) 
{
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


