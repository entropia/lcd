#include <stdio.h>
#include "output.h"

void main() {
    int i=0;
    putstring("Sende",10, 8, 2, 0);
    putstring("pause",10,24, 2, 0);
    while(1) {
        scrollup(1);
        writescreen();
        usleep(150000);
    }
}

