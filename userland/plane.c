#include <stdio.h>
#include <math.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i=0;
    int x=40,y=20;
    srandom(time(NULL));
    while(1) {
        if (i==0) {
            x=rand()%XSIZE;
            y=rand()%YSIZE;
            clearscreen();
        }
        printf("fljsdf\n");
        i=(i+1)%1000;

            x=XSIZE+(x-1+rand()%2) % XSIZE;
            y=YSIZE+(y-1+rand()%2) % YSIZE;
            setpixel(x,y);
            setpixel(x+1,y);
            setpixel(x+1,y+1);
            setpixel(x,y+1);
        
        writescreen();
        usleep(15000);
    }
    return 0;
}


