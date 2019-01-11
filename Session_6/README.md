
@Date : 8/1/2019
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-6
/*********************************************************************************************/
1.Process File System

File : My_ProcFs.c

Description :
               This file is which create process file in /proc dir and read and write from that proc file. 
		

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod My_Proc.ko
  kernel ring buffer
3.see the procfs entry in /proc directroy cat /proc/My_Proc
4. write in My_proc             echo "spanidea proc" > /proc/My_proc
5.Remove module                 sudo rmmod My_ProcFs
6.Run                           make clean

Key points :

->  proc_create();
->  remove_proc_entry();
->  #include<linux/proc_fs.h>






