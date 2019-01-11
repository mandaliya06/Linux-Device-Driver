/************************************************************************************************
@fileName : My_App.c
@author   : Kishan Mandaliya 
@teamLead : Rajesh Dommaraju 
@details  : It is Application code for drive driver from user space.
@license  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/************************************************************************************************
                        		INCLUDES
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int main()
{
        int fd;
        char option;
	int32_t value, number;
        printf("*********************************\n");
        printf("*******Spanidea : Device Driver*******\n");

        fd = open("/dev/My_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        1. IOCTL WRITE               \n");
                printf("        2. IOCTL READ                \n");
                printf("        3. Exit                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                printf("Enter the value to send : \n");
                                scanf("%d", &number);
                                printf("Writing value to Driver\n");
                                ioctl(fd,WR_VALUE,(int32_t*) &number);
                                break;
                        case '2':
                                printf("Reading value from Driver\n");
                                ioctl(fd,RD_VALUE,&value);
				printf("Value is = %d\n",value);
                                break;
                        case '3':
                                close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fd);
}
