/************************************************************************************************
@fileName : Hello_world.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is a module for Allocating major and minor number to device by Statically and Dynamically method.
@license  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/************************************************************************************************
                        		INCLUDES
************************************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

/**********************************************************************************************
                         		LOCAL MACROS           
**********************************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "KISHAN MANDALIYA"
#define DRIVER_MODULE_DESC                      "Statically & Dynamically  Allocating Major and Minor Number"
#define DRIVER_MODULE_VERSION                   "V1.1"
#define SUCCESS  0
#define FAILURE -1
#define STATIC_METHOD 1
/***********************************************************************************************
                         		LOCAL TYPEDEFS         
***********************************************************************************************/

/**********************************************************************************************
                        		GLOBAL VARIABLES                
**********************************************************************************************/
dev_t dev = MKDEV(5000,0);
/*********************************************************************************************
                        		LOCAL VARIABLES         
*********************************************************************************************/

/********************************************************************************************
                        		LOCAL FUNCTIONS         
********************************************************************************************/
static int Hello_World_init(void);
static void Hello_World_exit(void);
//int register_chrdev_region(dev_t, unsigned int, char *);
//void unregister_chrdev_region(dev_t, unsigned int);

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
    printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
    printk(KERN_DEBUG "File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
    return SUCCESS;
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
    unregister_chrdev_region(dev, 1);
    printk("Kernel Madule Removed Successfully...\n");
    printk("File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
}

module_init(Hello_World_init);
module_exit(Hello_World_exit);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);


