obj-m = My_INT.o My_INT_WQ.o My_Tasklet.o

KDIR = /lib/modules/$(shell uname -r)/build

all:

	make -C $(KDIR) M=$(shell pwd) modules

clean:
	
	make -C $(KDIR) M=$(shell pwd) clean
