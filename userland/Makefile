GCC=gcc
# CFLAGS=-pipe -Wall -ggdb -pg
CFLAGS=-O3 -Wall -g
LDFLAGS=-lm
LIBS=

all: plane scroller scroller2 clock test manuel
	@echo "Userland Programme fertig..."

.c.o:
	${GCC} ${CFLAGS} -c -o $@ $<

plane: plane.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} plane.o output.o -o plane

scroller: scroller.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} scroller.o output.o -o scroller
scroller2: scroller2.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} scroller2.o output.o -o scroller2

scroller-tnt: scroller-tnt.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} scroller-tnt.o output.o -o scroller-tnt

clock: clock.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} clock.o output.o -o clock

test: test.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} test.o output.o -o test

manuel: manuel.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} manuel.o output.o -o manuel

pong: pong.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} pong.o output.o -o pong

clean:
	rm -f plane scroller  clock test manuel
	rm -f *.o *~ core


