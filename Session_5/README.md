
@Date : 26/12/2018
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-3
/*********************************************************************************************/
1.Null Driver module

File : My_Driver.c

Description :
               This file is a simple Null Driver module.Contains open,read,write      
               and release function call. 
		

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod My_Driver.ko
3.See the write 1 in 
to device file        	        echo 1 > /dev/My_Device
  see the read from device file cat > /dev/My_Device
4.See the logs in dmesg         dmesg 
  kernel ring buffer
5.Remove module                 sudo rmmod My_Driver
6.Run                           make clean




