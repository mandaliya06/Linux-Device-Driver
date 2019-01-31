
@Date : 21/1/2019
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-9
/*********************************************************************************************/
1.Spinlock

File : My_Spinlock.c

Description :
               spinlock. 
		

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod My_SysFs.ko
  kernel ring buffer
3.see the sysfs entry in 
/sys/kernel directroy 		cat /sys/kernel/My_SysFs/My_value
4. write in My_proc             echo 1234 > /sys/kernel/My_sysFs/My_value
5.Remove module                 sudo rmmod My_SysFs
6.Run                           make clean

Key points :

