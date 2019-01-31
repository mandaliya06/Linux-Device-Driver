/*************************************************************************************************
@fileName : Hello_world.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is a simple HelloWorld driver to Passing Arguments to Device Driver  
@license  : SpanIdea Systems Pvt. Ltd. All rights reserved.
*************************************************************************************************/

/*************************************************************************************************
                        INCLUDES
*************************************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
/*************************************************************************************************
                         LOCAL MACROS           
*************************************************************************************************/

#define GPL_LICENSE                             "GPL"
#define DRIVER_MODULE_AUTHOR                    "KISHAN MANDALIYA"
#define DRIVER_MODULE_DESC                      "Passing Arguments to Device Driver"
#define DRIVER_MODULE_VERSION                   "V1.1"

/*************************************************************************************************
                         LOCAL TYPEDEFS         
*************************************************************************************************/

/*************************************************************************************************
                        GLOBAL VARIABLES                
*************************************************************************************************/

int  val,arr_val[4];
char *name;
int  cb_val = 0;

/*************************************************************************************************
                        LOCAL VARIABLES         
*************************************************************************************************/

/*************************************************************************************************
                        LOCAL FUNCTIONS         
*************************************************************************************************/

static int Hello_World_init(void);
static void Hello_World_exit(void);

module_param(val,int,S_IRUSR|S_IWUSR);                //integer value
module_param(name,charp,S_IRUSR|S_IWUSR);             //String
module_param_array(arr_val,int,NULL,S_IRUSR|S_IWUSR); //Array of integers

/*************************************************************************************************
function         : notify_param
description      : This function is notify when variable would be changed.
            
input param      : integer value
output param     : On success 0 else -1
*************************************************************************************************/
int notify_param(const char *val,const struct kernel_param *kp)
{
	
	int res = param_set_int(val,kp); // Use helper for write variable
	if(res == 0){
		printk(KERN_INFO "Call back function called...\n");
		printk(KERN_INFO "New value of cb_val = %d\n", cb_val);
		return 0;
	}
	return -1;
}

const struct kernel_param_ops my_param_ops =
{
	.set = &notify_param,  
	.get = &param_get_int, 
};
/**********************************************************************************************
function         : module_param_cb
description      : To register the callback whenever the argument(parameter) got changed            
**********************************************************************************************/

module_param_cb(cb_val,&my_param_ops, &cb_val, S_IRUGO|S_IWUSR);

/**********************************************************************************************
function         : Hello_World_init
description      : This function is initialised when module gets inserted.
                   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static int __init Hello_World_init(void) 
{

    int i;
    printk(KERN_INFO "val = %d \n", val);
    printk(KERN_INFO "cb_val = %d \n", cb_val);
    printk(KERN_INFO "name = %s \n",name);
    for(i =0; i < (sizeof arr_val/ sizeof (int)); i++)
    {
    	printk(KERN_INFO "arr_val[%d] = %d\n",i,arr_val[i]);
    }
    printk(KERN_INFO  "Hello World module inserted...\n");
    printk(KERN_DEBUG "File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
    return 0;
}

/**********************************************************************************************
function         : Hello_World_exit
description      : This function is initialised when module gets removed.
                   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
static void __exit Hello_World_exit(void) {
    printk("Hello world module removed...\n");
    printk("File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
}

module_init(Hello_World_init);
module_exit(Hello_World_exit);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);


