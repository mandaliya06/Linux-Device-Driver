
@Date : 17/12/2018
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-2

/*********************************************************************************************/
1.Passing Arguments to Device Driver

File : Hello_World.c
Description :
                This file is a simple Hello World module and Passing Arguments to Device Driver.
                Contains basic module_init and module_exit functions.

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod Hello_World.ko val=10 name="Spanidea" arr_val=10,11,12,13
3.See the added module          cat /proc/modules | grep Hello_World
4.See the logs in dmesg         dmesg | tail -10
  kernel ring buffer
5.Now i’m going to check 
module_param_cb() is weather	echo 15 > /sys/module/Hello_World/parameters/cb_val  
calling that handler function 
or not. For that i need to 
change the variable in sysfs.

6.Remove module                 sudo rmmod Hello_World
7.Run                           make clean


Keypoints to remember:
1.static int Hello_World_init();
2.void Hello_World_exit();
3.module_init();
4.module_exit();
5.module_param()
6.module_param_array()
7.module_param_cb() // cb mean callback

