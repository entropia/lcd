#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include "output.h"

int ballx, bally;
int speedx, speedy;

void update_ball() {
   ballx += speedx;
   if (ballx > 103) {
      speedx = -speedx;
      ballx = 103;
   } else if (ballx < 0) {
      speedx = -speedx;
      ballx = 0;
   }

   bally += speedy;
   if (bally > 55) {
      speedy = -speedy;
      bally = 55;
   } else if (bally < 0) {
      speedy = -speedy;
      bally = 0;
   }
}

void main() {
   struct timeval tv;

   gettimeofday(&tv, NULL);
   srand(tv.tv_usec);

   ballx = rand()%103;
   bally = rand()%55;
   speedx = rand()%8 - 4;
   speedy = rand()%8 - 4;

   if (speedx == 0) speedx++;
   if (speedy == 0) speedy++;

   while (1) {
      clearscreen();
      update_ball();
      setblock(ballx, bally, ballx+3, bally+3);
      writescreen();
      usleep(30000);
   }
}
