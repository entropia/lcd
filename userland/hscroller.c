#include <stdio.h>
#include "output.h"

#define MIN(a,b) ((a)<(b)?(a):(b))

char *text;
int textoffset=0;

int bottomlinepos;
char line[12];

void neueletztezeile(int charpos) {
#define CHAR_AT(line, pos) ((pos)>=strlen(line)?' ':line[pos])
    int i;
    for (i=0; i<11; i++) {
        line[i] = charpos + i >= strlen(text) ? ' ' : text[charpos + i];
    }
    line[11] = 0;
    bottomlinepos = YSIZE;
}

void main(int argc, char *argv[]) {

    if (argc<2) {
        printf("geh weg");
        exit(-42);
    }
    
    neueletztezeile(0);

    while(1) {
        int i;
        scrollup(1);
        bottomlinepos--;
        if (bottomlinepos<=YSIZE-10) {
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

