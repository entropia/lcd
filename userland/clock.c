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
        putstring(buf, 10,          2,  4, -3);
	for (x=0; x<60; x++) {
		setpixel(10+x, 55);
		if (x<tl->tm_sec){
			setpixel(10+x, 56);
			setpixel(10+x, 56);
		}
	}
	for (x=0; x<20; x++) {
		setpixel(-sin(tl->tm_sec/60.0*3.14*2)*x+50, -cos(tl->tm_sec/60.0*3.14*2)*x+33);
		
        }
	for (x=0; x<100; x++) {
		setpixel(-sin(x/100*3.14*2)*20+50, -cos(x/100*3.14*2)*20+33);
		
        }
        writescreen();
        usleep(15000);
    }
    return 0;
}


