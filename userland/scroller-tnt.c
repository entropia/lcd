#include <stdio.h>
#include <math.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i, j;
    int strwidth;
    if (argc<2) {
        printf("geh weg");
        exit(-42);
    }
    
    strwidth = stringwidth(argv[1], 6, -5);

    for (i=0; i< strwidth; i++) {
        clearscreen();
        putstring(argv[1], -i,          8+sin(i/3.0)*8,  4, -5);
        putstring(argv[1], -i*2,          36+sin(i/4.0)*8,  1, 0);
        for (j=0; j < 100; j++) {
           setpixel(sin(j/(1.0+i))*30+50,cos(j/(1.0+i))*30+33);
        }
        writescreen();
        usleep(15000);
    }
    return 0;
}


