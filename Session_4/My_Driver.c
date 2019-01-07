/************************************************************************************************
@fileName : My_Driver.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is a module for Null driver code,In this code,we can do all open,read,write,close.
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

/**********************************************************************************************
                         		LOCAL MACROS           
**********************************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "KISHAN MANDALIYA"
#define DRIVER_MODULE_DESC                      "Null Driver Coder"
#define DRIVER_MODULE_VERSION                   "V1.3"
#define SUCCESS  0
#define FAILURE -1
/***********************************************************************************************
                         		LOCAL TYPEDEFS         
***********************************************************************************************/

/**********************************************************************************************
                        		GLOBAL VARIABLES                
**********************************************************************************************/
dev_t dev = 0;
static struct class *dev_class;
static struct cdev My_cdev;


/*********************************************************************************************
                        		LOCAL VARIABLES         
*********************************************************************************************/

/********************************************************************************************
                        		LOCAL FUNCTIONS         
********************************************************************************************/
static int  __init My_Driver_init(void);
static void __exit My_Driver_exit(void);
static int My_open(struct inode *inode, struct file *file);
static int My_release(struct inode *inode, struct file *file);
static ssize_t My_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t My_write(struct file *filp, const char *buf, size_t len, loff_t *off);


static struct file_operations fops =
{
.owner		= THIS_MODULE,
.read		= My_read,
.write		= My_write,
.open		= My_open,
.release	= My_release,
};


/**********************************************************************************************
function         : My_Driver_init
description      : This function is initialised when module gets inserted.
                   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static int __init My_Driver_init(void) 
{
    //register_chrdev_region(dev, 1, "Spanidea"); //statically Allocating major number

    /* Allocating major number */
    if((alloc_chrdev_region(&dev, 0, 1, "Spanidea"))<0){
		printk(KERN_INFO "Cannot allocate major numer \n");
		return FAILURE;
    }
    printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

    /* Creating cdev Structure */
    cdev_init(&My_cdev, &fops);
   
    /* Adding character device to the system */
    if((cdev_add(&My_cdev, dev, 1))< 0){
	printk(KERN_INFO "Can not add the device to the system \n");
	goto r_class;
    }

    /* Creating struct class */
    if((dev_class = class_create(THIS_MODULE, "My_class")) == NULL){
	printk(KERN_INFO "Can not create the struct class \n");
	goto r_class;
    }
    /* Creating device */
    if((device_create(dev_class, NULL, dev, NULL, "My_device")) == NULL){
	printk(KERN_INFO "Can not create the device \n");
	goto r_device;
    }
    printk(KERN_INFO "My Driver Insert...Done!!!!!! \n");
  return SUCCESS;

r_device : 
	class_destroy(dev_class);
r_class  :
	unregister_chrdev_region(dev ,1);
	return FAILURE;
}

/**********************************************************************************************
function         : My_Driver_exit
description      : This function is initialised when module gets removed.
                   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static void __exit My_Driver_exit(void) 
{
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&My_cdev);
    unregister_chrdev_region(dev, 1);
    printk("My Driver Remove...Done!!! \n");
}

static int My_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "My Driver Open Function Called...!!! \n");
	return SUCCESS;
}

static int My_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "My Driver Release Function Called...!!! \n");
	return SUCCESS;
}

static ssize_t My_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "My Driver Read Function called...!!! \n");
	return SUCCESS;

}

static ssize_t My_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "My Driver Write Function called...!!! \n");
	return len;

}


module_init(My_Driver_init);
module_exit(My_Driver_exit);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);


