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
       for (i=0; i< 7; i++) {
          putstring(argv[1],(100-j*i) % 300,i*8,1,1);   
       } 
       writescreen();
       usleep(15000);
    }
    return 0;
}


