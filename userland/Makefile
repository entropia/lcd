GCC=gcc
# CFLAGS=-pipe -Wall -ggdb -pg
CFLAGS=-O3 -Wall -g
LDFLAGS=
LIBS=

all: scroller test
	@echo "Userland Programme fertig..."

.c.o:
	${GCC} ${CFLAGS} -c -o $@ $<

scroller: scroller.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} scroller.o output.o -o scroller

test: test.o output.o
	${GCC} ${CFLAGS} ${LDFLAGS} test.o output.o -o test

clean:
	rm -f scroller
	rm -f *.o *~ core


