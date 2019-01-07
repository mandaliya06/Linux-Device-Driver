
@Date : 3/1/2019
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-2

/*********************************************************************************************/
1. Make one function available to other modules by using Export_symbol  


File : Module_1.c Module_2.c
Description :
                This file is for how to make our functions available to other modules

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod Module_1.ko
				sudo insmod Module_2.ko
3.See the logs in dmesg         dmesg | tail 
  kernel ring buffer
4.Remove module                 sudo rmmod Module_1
				sudo rmmod Module_2

5.Run                           make clean


Keypoints to remember:
1.int Hello_World_init();
2.void Hello_World_exit();
3.module_init();
4.module_exit();
5.EXPORT_SYMBOL() helps you provide APIs to other modules/code.

