/************************************************************************************************
@FileName : Module_2.c
@author   : Kishan Mandaliya
@teamLead : Rajesh Dommaraju 
@Details  : Make one function available to other modules by using Export_symbol  
@License  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/*******************************************************************************
                        INCLUDES
*******************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>


/*******************************************************************************
                         LOCAL MACROS           
*******************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "SPANIDEA"
#define DRIVER_MODULE_DESC                      "Module to demonstrate the EXPORT_SYMBOL functionality"
#define DRIVER_MODULE_VERSION                   "V1.0"

/*****************************************************************************
                        GLOBAL VARIABLES
******************************************************************************/

extern void print_hello(int num);
extern int My_var;
extern char *str;


/**********************************************************************************************
function         : my_init
description      : This function is initialised when module gets inserted.
                   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/

static int my_init(void)
{
	printk(KERN_INFO "Hello from 2nd Module...\n");
	print_hello(5);

	printk(KERN_INFO "value of My_var = %d\n",My_var);
	printk(KERN_INFO "name  = %s\n",str);
	
	return 0;
}

/**********************************************************************************************
function         : my_exit
description      : This function is initialised when module gets removed.
                   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static void my_exit(void)
{
	printk(KERN_INFO "Bye!!! from 2nd Module...\n");

}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION(DRIVER_MODULE_DESC);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_LICENSE(GPL_LICENSE);
MODULE_VERSION(DRIVER_MODULE_VERSION);
