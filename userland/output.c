#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "output.h"

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
    }

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

void setblock(int x1, int y1, int x2, int y2) {
    int x,y;
    if (x1>x2 || y1>y2)
        return;
    if (x1<0) x1=0;
    if (x2>=XSIZE) x2=XSIZE-1;
    if (y1<0) y1=0;
    if (y2>=YSIZE) y2=YSIZE-1;

    for (y=y1; y<=y2; y++) {
        for (x=x1; x<=x2; x++) {
            SCR_AT(x, y)=1;
        }
    }
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

void scrollup(int lines) {
    if (lines == 0)
        return;
    if (lines>=YSIZE) 
        lines=YSIZE-1;
    memmove(&SCR_AT(0,0), &SCR_AT(0, lines), (YSIZE-lines+1)*XSIZE);
    bzero(&SCR_AT(0, lines), lines*XSIZE);
}
