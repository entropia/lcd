#include <stdio.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i;
    int strwidth;
    if (argc<2) {
        printf("geh weg");
        exit(-42);
    }
    
    strwidth = stringwidth(argv[1], 4, 1);

    for (i=0; i< strwidth; i+=5) {
        clearscreen();
        putstring(argv[1], -i,          0,  4, 1);
        putstring(argv[1], -strwidth+i, 30, 4, 1);
        writescreen();
    }
    return 0;
}


