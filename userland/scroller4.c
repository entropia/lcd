#include <stdio.h>
#include <math.h>
#include "output.h"


void kreis(int x,int y, double r) {
   int i;
   
   for (i=0;i<100;i++) {
      putpixel(x+sin(i/100.0*3.14*2)*r,y+cos(i/100.0*3.14*2)*r);
   }
}

void wkreis(int x,int y, double r,double w1, double w2) {
   int i;
   
   for (i=(w1/360*2*3.14*100);i<w2/360*3.14*2*100;i++) {
      putpixel(x+sin(i/100.0)*r,y-cos(i/100.0)*r);
   }
}

void zeiger(int x,int y, double r, double w) {
   int i;
   
   for (i=0;i<=r;i++) {
      putpixel(x+sin(w/360*2*3.14)*i,y-cos(w/360*3.14*2)*i);
   }
}

int mund; 

void pacman(int x, int y) {
   int m;
   
   m = sin(mund/2.0)*10+10;
   mund++;
   
   wkreis(x,y,15,90+m,360+90-m);
   if (m > 10) { kreis(x+4,y-9,2); }

   zeiger(x,y,15,90+m);
   zeiger(x,y,15,90-m);
   kreis(x+5,y-8,4);
}

int main() {
   for (;;) {
   clearscreen();
   pacman(mund % 110,30);
   writescreen();
   usleep(50000);
   }
   return 0;
}


