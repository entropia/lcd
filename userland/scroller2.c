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
    
    strwidth = stringwidth(argv[1], 1, 1);

    for (j=0; j< 1000 ; j++) {   
       clearscreen();
       putstring(argv[1],(100-j*1) % 300,  sin(j/10.0)*8+8,1,1);   
       putstring(argv[1],(100-j*2) % 300,  sin(j/5.0)*8+16,1,1);   
       putstring(argv[1],(100-j*3) % 300,  sin(j/7.0)*8+24,1,1);   
       putstring(argv[1],(100-j*2) % 300,  sin(j/9.0)*8+32,1,1);   
       putstring(argv[1],(100-j*1) % 300,  sin(j/5.0)*8+40,1,1);   
       writescreen();
       usleep(1500);
    }
    return 0;
}


