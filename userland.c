#include <sys/io.h>

#define PORT_BASE 0x378

#define LCD_DEBUG 1

#define LCD_PIN_RES 1
#define LCD_PIN_SCL (1 << 1)
#define LCD_PIN_SI (1 << 2)
#define LCD_PIN_RS (1 << 3)
#define LCD_PIN_CS (1 << 4)
#define LCD_PIN_VCC (1 << 5)

#undef LDEBUG
#ifdef LCD_DEBUG
#  define LDEBUG(fmt, args...) printf("lcd: " fmt, ## args)
#else
#  define LDEBUG(fmt, args...)
#endif

#define LCD_SET(adress, sig) outb(inb(adress) | sig, adress)
#define LCD_UNSET(adress, sig) outb(inb(adress) & ~sig, adress)

#define LCD_DELAY_S 0
#define LCD_DELAY_L 5000

void mysleep() {
   int i;

   //for (i=0; i<100; i++);
}

void lcd_send_command(unsigned long address, unsigned char data) {
   int i;
   unsigned char send;

   /* RES = 1, RS = 0, SCL = 1, CS = 0 */
   LCD_UNSET(address, LCD_PIN_RS);
   LCD_SET(address, LCD_PIN_SCL);
   LCD_UNSET(address, LCD_PIN_CS);
   

   for (i=0; i<8; i++) {
      send = 0;

      if (data & (128 >> i)) 
         LCD_SET(address, LCD_PIN_SI);
      else
         LCD_UNSET(address, LCD_PIN_SI);

      /* ack */
      LCD_UNSET(address, LCD_PIN_SCL);
      
      LCD_SET(address, LCD_PIN_SCL);
      
   }

   LCD_SET(address, LCD_PIN_CS);
}

void lcd_send_data(unsigned long address, unsigned char data) {
   int i;
   unsigned char send;

   printf("send_data\n");

   /* RES = 1, RS = 1, SCL = 1, CS = 0 */
   LCD_SET(address, LCD_PIN_RS);
   LCD_SET(address, LCD_PIN_SCL);
   LCD_UNSET(address, LCD_PIN_CS);
   

   printf("send_data2\n");
   for (i=0; i<8; i++) {
      send = 0;

      if (data & (128 >> i)) 
         LCD_SET(address, LCD_PIN_SI);
      else
         LCD_UNSET(address, LCD_PIN_SI);

      /* ack */
      LCD_UNSET(address, LCD_PIN_SCL);
      
      LCD_SET(address, LCD_PIN_SCL);
      
   }
   printf("send_data3\n");

   LCD_SET(address, LCD_PIN_CS);
}

void lcd_init(unsigned long address) {
   LCD_SET(address, LCD_PIN_VCC);
   LCD_UNSET(address, LCD_PIN_RES);
   
   LCD_SET(address, LCD_PIN_RES);
   

   lcd_send_command(address, 226);      /* ResetCommand */
   lcd_send_command(address, 161);      /* ADCL */
   lcd_send_command(address, 163);      /* SelBias9 */
   lcd_send_command(address, 0x2f);     /* VConverterOn */
   lcd_send_command(address, 129);      /* SetEVC */
   lcd_send_command(address, 20);       /* EVC */
   lcd_send_command(address, 175);      /* Dispon */
   lcd_send_command(address, 197);      /* EntDispon */
   lcd_send_command(address, 128+64+8); /* SHLR */
}

void main() {
   int i, j;

   if (ioperm(PORT_BASE, 3, 1)) {
      printf("bla\n");
      exit(1);
   }

   lcd_init(PORT_BASE);
   for (i=0; i<=8; i++) {
      lcd_send_command(PORT_BASE, 176+i);
      lcd_send_command(PORT_BASE, 16);
      lcd_send_command(PORT_BASE, 0);
      for (j=0; j<=130; j++) 
         lcd_send_data(PORT_BASE, 0x00);
   }
   for (i=0; i<=8; i++) {
      lcd_send_command(PORT_BASE, 176+i);
      lcd_send_command(PORT_BASE, 16);
      lcd_send_command(PORT_BASE, 0);
      for (j=0; j<=116; j++) 
         lcd_send_data(PORT_BASE, 0xff);
   }
}
