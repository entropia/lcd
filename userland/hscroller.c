#include <stdio.h>
#include "output.h"

#define MIN(a,b) ((a)<(b)?(a):(b))

char *text;
int textoffset=0;

int bottomlinepos;
char line[12];

void neueletztezeile(int pos) {
    int i;
    printf("%d\n", pos);
    for (i=0; i<11; i++) {
        line[i] = pos + i >= strlen(text) ? ' ' : text[pos + i];
    }
    line[11] = 0;
    bottomlinepos = YSIZE;
}

void main(int argc, char *argv[]) {

    if (argc<2) {
        printf("geh weg");
        exit(-42);
    }
    text=argv[1];
    
    neueletztezeile(0);

    while(1) {
        int i;

        scrollup(1);
        bottomlinepos--;
        
        if (bottomlinepos<=YSIZE-10) {
            printf("neue letzte zeile\n");
            textoffset+=11;
            if (textoffset > strlen(text))
                textoffset = 0;
            neueletztezeile(textoffset);
        }
        for (i=0; i<11; i++) {
            putcharacter(line[i], i*9, bottomlinepos, 1);
        }
        writescreen();
        usleep(150000);
    }
}

