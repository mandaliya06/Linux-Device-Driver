/************************************************************************************************
@fileName : My_Real_Driver.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is a module for reading And writing data into driver. 
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
/**********************************************************************************************
                         		LOCAL MACROS           
**********************************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "KISHAN MANDALIYA"
#define DRIVER_MODULE_DESC                      "Real Driver Code"
#define DRIVER_MODULE_VERSION                   "V1.4"
#define SUCCESS  0
#define FAILURE -1
#define MEM_SIZE    1024

/***********************************************************************************************
                         		LOCAL TYPEDEFS         
***********************************************************************************************/

/**********************************************************************************************
                        		GLOBAL VARIABLES                
**********************************************************************************************/

dev_t dev = 0;
static struct class *dev_class;
static struct cdev My_cdev;
uint8_t *kernel_buffer;

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
static ssize_t My_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t My_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = My_read,
        .write          = My_write,
        .open           = My_open,
        .release        = My_release,
};

static int My_open(struct inode *inode, struct file *file)
{
        /*Creating Physical memory*/
        if((kernel_buffer = kmalloc(MEM_SIZE, GFP_KERNEL)) == 0){
            printk(KERN_INFO "Cannot allocate memory in kernel\n");
            return FAILURE;
        }
        printk(KERN_INFO "Device File Opened...!!!\n");
        return SUCCESS;
}

static int My_release(struct inode *inode, struct file *file)
{
        kfree(kernel_buffer);
        printk(KERN_INFO "Device File Closed...!!!\n");
        return 0;
}

static ssize_t My_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        copy_to_user(buf, kernel_buffer, MEM_SIZE);
        printk(KERN_INFO "Data Read : Done!\n");
        return MEM_SIZE;
}
static ssize_t My_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        copy_from_user(kernel_buffer, buf, len);
        printk(KERN_INFO "Data Write : Done!\n");
        return len;
}

/**********************************************************************************************
function         : My_Driver_init
description      : This function is initialised when module gets inserted.
                   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/

static int __init My_Driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "My_Dev")) <0){
                printk(KERN_INFO "Cannot allocate major number\n");
                return FAILURE;
        }
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

        /*Creating cdev structure*/
        cdev_init(&My_cdev,&fops);
        My_cdev.owner = THIS_MODULE;
        My_cdev.ops = &fops;

        /*Adding character device to the system*/
        if((cdev_add(&My_cdev,dev,1)) < 0){
            printk(KERN_INFO "Cannot add the device to the system\n");
            goto r_class;
        }

        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"My_class")) == NULL){
            printk(KERN_INFO "Cannot create the struct class\n");
            goto r_class;
        }

        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"My_device")) == NULL){
            printk(KERN_INFO "Cannot create the Device 1\n");
            goto r_device;
        }
        printk(KERN_INFO "Device Driver Insert...Done!!!\n");
	return 0;

r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

/**********************************************************************************************
function         : My_Driver_exit
description      : This function is initialised when module gets removed.
                   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
void __exit My_Driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&My_cdev);
        unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "Device Driver Remove...Done!!!\n");
}

module_init(My_Driver_init);
module_exit(My_Driver_exit);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);


