#include <stdio.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i;
    int strwidth;
    if (argc<2) {
        printf("geh weg");
        exit(-42);
    }
    
    strwidth = stringwidth(argv[1], 6, 1);

    for (i=0; i< strwidth; i+=5) {
        clearscreen();
        putstring(argv[1], -i,          0,  6, 0);
        writescreen();
        usleep(100000);
    }
    return 0;
}


