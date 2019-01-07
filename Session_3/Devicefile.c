/************************************************************************************************
@fileName : Devicefile.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is a module for Creating Device file.
@license  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/************************************************************************************************
                        		INCLUDES
************************************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>

/**********************************************************************************************
                         		LOCAL MACROS           
**********************************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "KISHAN MANDALIYA"
#define DRIVER_MODULE_DESC                      "Creating Device file"
#define DRIVER_MODULE_VERSION                   "V1.2"
#define SUCCESS  0
#define FAILURE -1
#define STATIC_METHOD 0
/***********************************************************************************************
                         		LOCAL TYPEDEFS         
***********************************************************************************************/

/**********************************************************************************************
                        		GLOBAL VARIABLES                
**********************************************************************************************/
dev_t dev = 0;
static struct class *dev_class;
/*********************************************************************************************
                        		LOCAL VARIABLES         
*********************************************************************************************/

/********************************************************************************************
                        		LOCAL FUNCTIONS         
********************************************************************************************/
static int Hello_World_init(void);
static void Hello_World_exit(void);

/**********************************************************************************************
function         : Hello_World_init
description      : This function is initialised when module gets inserted.
                   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static int __init Hello_World_init(void) 
{
    if(STATIC_METHOD)
    {
    	register_chrdev_region(dev, 1, "Spanidea"); //statically Allocating major number
    }
    else
    {
    	if((alloc_chrdev_region(&dev, 0, 1, "Spanidea"))<0){
		printk(KERN_INFO "Cannot allocate major numer for devices \n");
		return FAILURE;
	    }
    }
    printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

    /* Creating struct class*/
    if((dev_class = class_create(THIS_MODULE, "ext_device")) ==  NULL){
	printk(KERN_INFO "Can't create the struct class for device \n");
	goto r_class;
    }
    /* Creating device */
    if((device_create(dev_class, NULL, dev, NULL, "ext_device")) == NULL){
         printk(KERN_INFO "Can't create the device \n");
	 goto r_device;
    }
    printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
  return SUCCESS;

r_device : 
	 class_destroy(dev_class);
r_class  :
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
static void __exit Hello_World_exit(void) 
{
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    unregister_chrdev_region(dev, 1);
    printk("Kernel Madule Removed Successfully...\n");
}

module_init(Hello_World_init);
module_exit(Hello_World_exit);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);


