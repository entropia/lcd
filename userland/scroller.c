#include <stdio.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i;
    int strwidth;
    if (argc<2) {
        printf("geh weg");
        exit(-42);
    }
    
    strwidth = stringwidth(argv[1], 6, -5);

    for (i=0; i< strwidth; i++) {
        clearscreen();
        putstring(argv[1], -i,          0,  4, -5);
        putstring(argv[1], -i*2,          36,  1, 0);
        writescreen();
        usleep(15000);
    }
    return 0;
}


