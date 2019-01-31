/********************************************************************************************************
@fileName : Hello_world.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is a simple HelloWorld driver to load a module in the kernel.  
@license  : SpanIdea Systems Pvt. Ltd. All rights reserved.
********************************************************************************************************/

/********************************************************************************************************
                        INCLUDES
********************************************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/********************************************************************************************************
                         LOCAL MACROS           
********************************************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "KISHAN MANDALIYA"
#define DRIVER_MODULE_DESC                      "Simple Hello World Module"
#define DRIVER_MODULE_VERSION                   "V1.0"
#define SUCCESS		0
#define FAILURE	       -1

/********************************************************************************************************
                         LOCAL TYPEDEFS         
********************************************************************************************************/

/********************************************************************************************************
                        GLOBAL VARIABLES                
********************************************************************************************************/

/********************************************************************************************************
                        LOCAL VARIABLES         
********************************************************************************************************/

/********************************************************************************************************
                        LOCAL FUNCTIONS         
********************************************************************************************************/

static int  __init Hello_World_init(void);
static void __exit Hello_World_exit(void);

/********************************************************************************************************
function         : Hello_World_init
description      : This function is initialised when module gets inserted.
                   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
********************************************************************************************************/

static int __init Hello_World_init(void) 
{

        printk(KERN_INFO "Yes!!!...Hello World module inserted...\n");
	printk(KERN_DEBUG "FILE : %s, fUNCTION : %s, LINE : %d \n", __FILE__, __func__, __LINE__);
	return SUCCESS;
}

/********************************************************************************************************
function         : Hello_World_exit
description      : This function is initialised when module gets removed.
                   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
********************************************************************************************************/

static void __exit Hello_World_exit(void) 
{
	printk(KERN_INFO "Hello world module removed...\n");
	printk(KERN_DEBUG "FILE : %s, fUNCTION : %s, LINE : %d \n", __FILE__, __func__, __LINE__);
    
}

module_init(Hello_World_init);
module_exit(Hello_World_exit);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);












