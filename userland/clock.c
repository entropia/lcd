#include <stdio.h>
#include <time.h>
#include "output.h"
#include <math.h>

int main(int argc, char *argv[]) {
    struct tm *tl;
	time_t t;    
	int x;
        int i, strwidth;


    if (argc<2) {
        printf("geh weg");
        exit(-42);
    }
    
    strwidth = stringwidth(argv[1], 1, -2) * 2;

    while(1) {
       char buf[1000];

       t = time(NULL);
       tl = localtime(&t);

        clearscreen();
	for (x=0; x<20; x++) {
		setpixel(50+sin(tl->tm_sec/60.0*3.14*2)*x, 33-cos(tl->tm_sec/60.0*3.14*2)*x);
        }
	for (x=0; x<15; x++) {
		setpixel(50+sin(tl->tm_min/60.0*3.14*2)*x, 33-cos(tl->tm_min/60.0*3.14*2)*x);
        }
	for (x=0; x<10; x++) {
		setpixel(50+sin(tl->tm_hour/60.0*3.14*2)*x, 33-cos(tl->tm_hour/60.0*3.14*2)*x);
		
        }
	for (x=0; x<100; x++) {
		setpixel(-sin(x/100.0*3.14*2)*20+50, -cos(x/100.0*3.14*2)*20+33);
		
        }
        putstring(argv[1], -(i++%strwidth),          8+sin(i/3.0)*8,  1, -2);
        putstring(argv[1], -((i*2)%strwidth),          32+sin(i/3.0)*8,  1, -2);
        writescreen();
        usleep(50000);
    }
    return 0;
}


