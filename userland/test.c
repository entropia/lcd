#include <stdio.h>
#include "output.h"

void main() {
    int i=0;
    putstring("Sende",10, 8, 2, 0);
    putstring("Sende",11, 9, 2, 0);
    putstring("Sende",10, 9, 2, 0);
    putstring("pause",10,24, 2, 0);
    putstring("pause",11,25, 2, 0);
    putstring("pause",10,25, 2, 0);
    writescreen();
}

