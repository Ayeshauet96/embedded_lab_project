MODULE_DIR := $(shell pwd)     
KERNEL_DIR := /root/LINUX/linux-4.19.107  	# here you need to give the path of latest compiled  
                                            	# kernel source path for Ubuntu desktop 
obj-m += mat-em.o

module:
	make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules
