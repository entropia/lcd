#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "../lcd.h"

// Define für asciitest
//#define TEST
#define CLRSCR "\27[2J" // FIXME


char screen[XSIZE*YSIZE]; 
#define SCR_AT(x,y) screen[(x)+(y)*XSIZE]

char font[256*8] = {
#include "font.h"
};

#define FONTBIT(c, x, y) (font[(c)*8+(y)] & (1<<(7-(x))))

void writescreen() {
#ifdef TEST
    int x, y;
    //printf(CLRSCR);
    for (y=0; y<YSIZE; y++) {
        for (x=0; x<XSIZE; x++) {
            if (SCR_AT(x,y)) 
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n");
#else    
    char buf[XSIZE*YSIZE/8];
    int bank, x, pos, bit;
    
    int devfp;

    #define SCR_SHIFT(x, bank, bit) (SCR_AT(x, (bank)*8 + bit) << bit)
    
    pos=0;
    for (bank = 0; bank < BANKS; bank++) {
        for (x = 0; x < XSIZE; x++) {
            buf[pos]=0;
            for (bit=0; bit < 8; bit++) {
                buf[pos] |= SCR_SHIFT(x, bank, bit);
            }
            pos++;
        }
    }

    devfp=open(DEVICE, O_WRONLY);
    write(devfp, &buf, XSIZE*YSIZE/8);
    close(devfp);

    printf("\n\n");
#endif
}

void clearscreen() {
    bzero(&screen, XSIZE*YSIZE);
}

void setpixel(int x, int y) {
    if (x>XSIZE || x<0 || y>YSIZE || y<0)
        return;

    SCR_AT(x, y)=1;
}

void unsetpixel(int x, int y) {
    if (x>XSIZE || x<0 || y>YSIZE || y<0)
        return;

    SCR_AT(x, y)=1;
}

void putcharacter(char blah, int x, int y, int zoom) {
    int bx, by, zoomx, zoomy;

    if (x > XSIZE || x + zoom * 8 < 0 || y > XSIZE || y + zoom * 8 < 0)
        return;

    for (by=0; by<8; by++) {
        for (bx=0; bx<8; bx++) {
            if (FONTBIT(blah, bx, by)) {
                for (zoomy=0; zoomy<zoom; zoomy++) {
                    for (zoomx=0; zoomx<zoom; zoomx++) {
                        setpixel(x+zoom*bx+zoomx, y+zoom*by+zoomy);
                    }
                }
            }
        }
    }
}

void putstring(char *string, int x, int y, int zoom, int spacing) {
    int i;
    for (i=0; i<strlen(string); i++) {
        putcharacter(string[i], x + i * ((zoom*8) + spacing), y, zoom);
    }
}

int stringwidth(char *string, int zoom, int spacing) {
    return (zoom*8+spacing)*strlen(string);
}
