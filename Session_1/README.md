
@Date : 11/12/2018
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-1

/*********************************************************************************************/
1.Writing "Frist" Driver "Hello World"

File : Hello_World.c
Description :
                This file is a simple Hello World module.
                Contains basic module_init and module_exit functions.

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod Hello_World.ko
3.See the added module          cat /proc/modules | grep Hello_World
4.See the logs in dmesg         dmesg | tail 
  kernel ring buffer
5.Remove module                 sudo rmmod Hello_World
6.Run                           make clean


Keypoints to remember:
1.int Hello_World_init();
2.void Hello_World_exit();
3.module_init();
4.module_exit();
5.In Makefile name should be start with capital latter M (E.g Makefile)




