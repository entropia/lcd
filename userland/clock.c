#include <stdio.h>
#include <time.h>
#include "output.h"
#include <math.h>

int main(int argc, char *argv[]) {
    struct tm *tl;
	time_t t;    
	int x;

    while(1) {
	    char buf[1000];
        clearscreen();
	t=time(NULL);
        tl=localtime(&t);
	sprintf(buf, "%02d:%02d", tl->tm_hour, tl->tm_min);
        putstring(buf, 10,          2,  2, -3);
	for (x=0; x<60; x++) {
		setpixel(10+x, 39);
		if (x<tl->tm_sec){
			setpixel(10+x, 40);
			setpixel(10+x, 41);
		}
	}
	for (x=0; x<20; x++) {
		setpixel(50+sin(tl->tm_sec/60.0*3.14*2)*x, 33-cos(tl->tm_sec/60.0*3.14*2)*x);
	for (x=0; x<15; x++) {
		setpixel(50+sin(tl->tm_min/60.0*3.14*2)*x, 33-cos(tl->tm_min/60.0*3.14*2)*x);
	for (x=0; x<10; x++) {
		setpixel(50+sin(tl->tm_hour/60.0*3.14*2)*x, 33-cos(tl->tm_hour/60.0*3.14*2)*x);
		
        }
	for (x=0; x<100; x++) {
		setpixel(-sin(x/100.0*3.14*2)*20+50, -cos(x/100.0*3.14*2)*20+33);
		
        }
        writescreen();
        usleep(500000);
    }
    return 0;
}


