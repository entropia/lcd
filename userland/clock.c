#include <stdio.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i;
    int strwidth;
    struct tm *tl;
    
    hile(1) {
	    char buf[1000];
        clearscreen();
        tl=localtime(time(NULL));
	sprintf(buf, "%02d:%02d", tl->tm_hour, tl->tm_min);
        putstring(buf, 10,          2,  4, -3);
	for (x=0, x<60; x++) {
		setpixel(10+x, 55);
		if (x<tl->tm_sec){
			setpixel(10+x, 56);
			setpixel(10+x, 56);
		}
	}
        writescreen();
        usleep(15000);
    }
    return 0;
}


