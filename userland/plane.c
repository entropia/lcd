#include <stdio.h>
#include <math.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i=0;
    int x=0,y=0;
    while(1) {
        if (i==0) {
            x=rand()%XSIZE;
            y=rand()%YSIZE;
            clearscreen();
        }
        i=(i+1)%1000;
        while (1) {
            x+=(XSIZE-rand()%3) % XSIZE;
            y+=(YSIZE-rand()%3) % YSIZE;
            setpixel(x,y);
            if (rand()%3 == 0)
                break;
        }
        
        writescreen();
        usleep(15000);
    }
    return 0;
}


