  PWD := $(shell pwd)
  KVER := $(shell uname -r)
  KDIR := /lib/modules/$(KVER)/build
  ccflags-y += -g
 
ksample-objs := ktest_drv.o
ksample-objs += ktest_proc.o
ksample-objs += ktest_ioctl.o

obj-m := ksample.o
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
.PHONY: aLL clean
