#include <linux/config.h>
#include <linux/module.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/fs.h>     /* everything... */
#include <linux/errno.h>  /* error codes */
#include <linux/delay.h>
#include <linux/malloc.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/tqueue.h>
#include <linux/poll.h>

#include <asm/io.h>

#include "lcd.h"

#define PORT_BASE 0x378

#define LCD_DEBUG 1

#define LCD_PORTS 1

#define LCD_PIN_RES 1
#define LCD_PIN_SCL (1 << 1)
#define LCD_PIN_SI (1 << 2)
#define LCD_PIN_RS (1 << 3)
#define LCD_PIN_CS (1 << 4)
#define LCD_PIN_VCC (1 << 5)

#undef LDEBUG
#ifdef LCD_DEBUG
#  define LDEBUG(fmt, args...) printk(KERN_DEBUG "lcd: " fmt, ## args)
#else
#  define LDEBUG(fmt, args...)
#endif

#define LCD_SET(adress, sig) outb(inb(adress) | sig, adress)
#define LCD_UNSET(adress, sig) outb(inb(adress) & ~sig, adress)

#define LCD_MAX_X XSIZE
#define LCD_MIN_X 11
#define LCD_MAX_Y BANKS
#define LCD_MIN_Y 0

static int major = 253; /* dynamic by default */
MODULE_PARM(major, "i");

static unsigned long base = PORT_BASE;
unsigned long lcd_base = 0;
MODULE_PARM(base, "l");

int lcd_x[LCD_PORTS], lcd_y[LCD_PORTS];

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

   /* RES = 1, RS = 1, SCL = 1, CS = 0 */
   LCD_SET(address, LCD_PIN_RS);
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

   lcd_send_command(address, 176);
   lcd_send_command(address, 16);
}

int lcd_open (struct inode *inode, struct file *filp)
{
   int port = (MINOR(inode->i_rdev)&0x0f);
   unsigned long address = lcd_base + port;

   LDEBUG("lcd_open\n");
   MOD_INC_USE_COUNT;

   lcd_init(address);

   lcd_x[port] = LCD_MIN_X;
   lcd_y[port] = LCD_MIN_Y;
   lcd_send_command(address, 176 + lcd_y[port]);
   lcd_send_command(address, 16);
   lcd_send_command(address, LCD_MIN_X);

   return 0;
}

int lcd_release (struct inode *inode, struct file *filp)
{
   LDEBUG("lcd_release\n");
   MOD_DEC_USE_COUNT;

   return 0;
}

ssize_t lcd_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
   LDEBUG("lcd_read count: %d\n", count);
   return -EFAULT;
}

ssize_t do_lcd_write (struct inode *inode, struct file *filp, const char *buf,
                size_t count, loff_t *f_pos)
{
   int retval = count, port = (MINOR(inode->i_rdev)&0x0f);
   unsigned long address = lcd_base + port;
   unsigned char *kbuf=kmalloc(count, GFP_KERNEL), *ptr;
   
    if (!kbuf) return -ENOMEM;
    if (copy_from_user(kbuf, buf, count))
       return -EFAULT;
    ptr=kbuf;
    
    while (count--) {
       lcd_send_data(address, *(ptr++));

       if (lcd_x[port]++ >= LCD_MAX_X) {
          lcd_x[port] = 0;

          if (lcd_y[port]++ >= LCD_MAX_Y)
             lcd_y[port] = 0;
          lcd_send_command(address, 176 + lcd_y[port]);
          lcd_send_command(address, 16);
          lcd_send_command(address, LCD_MIN_X);
       }

       wmb();
    }
    
    kfree(kbuf);
    return retval;
}

ssize_t lcd_write(struct file *filp, const char *buf, size_t count,
      loff_t *f_pos)
{
   LDEBUG("lcd_write count %d from %p\n", count, buf);
   return do_lcd_write(filp->f_dentry->d_inode, filp, buf, count, f_pos);
}

unsigned int lcd_poll(struct file *filp, poll_table *wait)
{
   LDEBUG("lcd_poll\n");
   return POLLIN | POLLRDNORM | POLLOUT | POLLWRNORM;
}

struct file_operations lcd_fops = {
   read: lcd_read,
   write: lcd_write,
   poll: lcd_poll,
   open: lcd_open,
   release: lcd_release,
};

int init_module(void) {
   int result, i;

   lcd_base = base;

   LDEBUG("init_module\n");

   /* Check for parallel port region */
   if ((result = check_region(lcd_base, 3)) < 0) 
      return  result;
   request_region(lcd_base, 3, "lcd");

   result = register_chrdev(major, "lcd", &lcd_fops);
   if (result < 0) {
      printk(KERN_INFO "lcd: can't get major number\n");
      release_region(lcd_base, 3);
      return result;
   }

   return 0;
}

void cleanup_module(void) {
   LDEBUG("cleanup_module\n");
   unregister_chrdev(major, "lcd");
   release_region(lcd_base, 3);
}

