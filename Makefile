KERNELDIR = /usr/src/linux

include $(KERNELDIR)/.config

LD_ADD = -I$(KERNELDIR)/include
CFLAGS = -D__KERNEL__ -DMODULE -I$(KERNELDIR)/include \
   -O -Wall

ifdef CONFIG_SMP
	CFLAGS += -D__SMP__ -DSMP
endif

all: driver.o
	@echo "Kernel Modul fertig"
	make -C userland

clean:
	rm -f *.o *~ core
	make -C userland clean


