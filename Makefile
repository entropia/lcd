KERNELDIR = /usr/src/linux

include $(KERNELDIR)/.config

LD_ADD = -I$(KERNELDIR)/include
CFLAGS = -D__KERNEL__ -DMODULE -I$(KERNELDIR)/include \
   -O -Wall

ifdef CONFIG_SMP
	CFLAGS += -D__SMP__ -DSMP
endif

all: driver.o

clean:
	rm -f *.o *~ core


