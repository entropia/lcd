#include "../lcd.h"

void writescreen();
void clearscreen();

void setpixel(int x, int y);
void unsetpixel(int x, int y);
#define putpixel(x, y) setpixel((x), (y))

void putcharacter(char blah, int x, int y, int zoom);
void putstring(char *string, int x, int y, int zoom, int spacing);
int  stringwidth(char *string, int zoom, int spacing);

void setblock(int x1, int y1, int x2, int y2);
void scrollup(int lines);
