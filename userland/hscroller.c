#include <stdio.h>
#include "output.h"

#define MIN(a,b) ((a)<(b)?(a):(b))
#define UNTEN YSIZE
char *text;
int textoffset=0;

int bottomlinepos;
char line[12];



void neueletztezeile(int pos) {
    int i;
    for (i=0; i<11; i++) {
        line[i] = pos + i >= strlen(text) ? ' ' : text[pos + i];
    }
    line[11] = 0;
    bottomlinepos = UNTEN;
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
        
        if (bottomlinepos<=UNTEN-10) {
            textoffset+=11;
            if (textoffset > strlen(text))
                textoffset = 0;
            neueletztezeile(textoffset);
        }
        for (i=0; i<11; i++) {
            putcharacter(line[i], 4+i*9, bottomlinepos, 1);
        }
        writescreen();
        usleep(15000);
    }
}

