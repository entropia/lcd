GCC=gcc
# CFLAGS=-pipe -Wall -ggdb -pg
CFLAGS=-O3 -Wall -g
LDFLAGS=-lm
LIBS=

all: plane scroller clock test manuel
	@echo "Userland Programme fertig..."

.c.o:
	${GCC} ${CFLAGS} -c -o $@ $<

plane: plane.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} plane.o output.o -o plane

scroller: scroller.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} scroller.o output.o -o scroller

scroller-tnt: scroller-tnt.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} scroller-tnt.o output.o -o scroller-tnt

clock: clock.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} clock.o output.o -o clock

test: test.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} test.o output.o -o test

manuel: manuel.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} manuel.o output.o -o manuel

clean:
	rm -f scroller
	rm -f *.o *~ core


