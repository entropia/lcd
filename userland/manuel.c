#include <stdio.h>
#include <math.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i, j;
    int strwidth, strwidth2;

    if (argc<2) {
        printf("geh weg");
        exit(-42);
    }
    
    strwidth = stringwidth(argv[1], 6, -5);
    strwidth2 = stringwidth(argv[1], 1, 0);

    printf("strwidth: %d %d\n", strwidth, strwidth2);

    for (i=0; i< strwidth; i++) {
        clearscreen();
        putstring(argv[1], -i,          8+sin(i/3.0)*8,  4, -5);
        putstring(argv[1], -((i*2)%strwidth),          36+sin(i/4.0)*8,  1, 0);
        printf("%d\n", -i*2);
        writescreen();
        usleep(15000);
    }
    return 0;
}


