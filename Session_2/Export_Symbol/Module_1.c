/************************************************************************************************
@FileName : Module_1.c
@author	  : Kishan Mandaliya
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

#define GPL_LICENSE				"GPL"
#define DRIVER_MODULE_AUTHOR			"SPANIDEA"
#define DRIVER_MODULE_DESC			"Module to demonstrate the EXPORT_SYMBOL functionality"
#define DRIVER_MODULE_VERSION			"V1.0"

/*****************************************************************************
			GLOBAL VARIABLES
******************************************************************************/
int My_var = 100;

EXPORT_SYMBOL(My_var);


void print_hello(int num)
{
	while(num--)
	{
		printk(KERN_INFO "from 1st Module : Hello friend\n");
	}
}
EXPORT_SYMBOL(print_hello);//making a function available for others to use


char *str = "Spanidea";
EXPORT_SYMBOL(str);


/**********************************************************************************************
function	 : my_init
description	 : This function is initialised when module gets inserted.
		   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/

static int __init my_init(void)
{
	printk(KERN_INFO  "Hello from 1st module...\n");
	return 0;
}
/**********************************************************************************************
function	 : my_exit
description	 : This function is initialised when module gets removed.
		   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/


static void __exit my_exit(void)
{
	printk(KERN_INFO  "Bye!!! from 1st Module...\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION(DRIVER_MODULE_DESC);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_LICENSE(GPL_LICENSE);
MODULE_VERSION(DRIVER_MODULE_VERSION);




/********************************** sudo cat /proc/kallsyms | grep "str" and cat symvers..........................
Doubt : If i having use both ,they give different address.It is not happening we will get same registered address only.why?????????????/

 *************************** */
