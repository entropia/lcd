#include <stdio.h>
#include <math.h>
#include "output.h"

int main(int argc, char *argv[]) {
    int i, j;
    int strwidth;
    if (argc<4) {
        printf("geh weg");
        exit(-42);
    }
    
    strwidth = stringwidth(argv[3], 1, 1);

    for (j=0; j< strwidth ; j++) {   
       clearscreen();
       putstring(argv[1],0,8*0,2,-2);   
       putstring(argv[2],0,8*2,1,-1);   
       putstring(argv[3],(100-j*4),8*5,1,1);   
       writescreen();
       usleep(200000);
    }
    return 0;
}


