#include <linux/config.h>
#include <linux/module.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/fs.h>     /* everything... */
#include <linux/errno.h>  /* error codes */
#include <linux/delay.h>  /* udelay */
#include <linux/malloc.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/tqueue.h>
#include <linux/poll.h>

#include <asm/io.h>

#define PORT_BASE 0x378

#define LCD_DEBUG 1

#undef LDEBUG
#ifdef LCD_DEBUG
#  define LDEBUG(fmt, args...) printk(KERN_DEBUG "lcd: " fmt, ## args)
#else
#  define LDEBUG(fmt, args...)
#endif

static int major = 253; /* dynamic by default */
MODULE_PARM(major, "i");

static unsigned long base = PORT_BASE;
unsigned long lcd_base = 0;
MODULE_PARM(base, "l");

int lcd_open (struct inode *inode, struct file *filp)
{
   LDEBUG("lcd_open\n");
   MOD_INC_USE_COUNT;
   return 0;
}

int lcd_release (struct inode *inode, struct file *filp)
{
   LDEBUG("lcd_release\n");
   MOD_DEC_USE_COUNT;
   return 0;
}

ssize_t do_lcd_read (struct inode *inode, struct file *filp, char *buf,
                size_t count, loff_t *f_pos)
{
   int retval = count;
   unsigned long address = lcd_base + (MINOR(inode->i_rdev)&0x0f);
   unsigned char *kbuf=kmalloc(count, GFP_KERNEL), *ptr;
   
   if (!kbuf) return -ENOMEM;
   ptr=kbuf;
   
   while (count--) {
      *(ptr++) = inb(address);
      rmb();
   }

   if ((retval > 0) && copy_to_user(buf, kbuf, retval))
      retval = -EFAULT;

   kfree(kbuf);
   return retval;
}

ssize_t lcd_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
   LDEBUG("lcd_read count: %d\n", count);
   return do_lcd_read(filp->f_dentry->d_inode, filp, buf, count, f_pos);
}

ssize_t do_lcd_write (struct inode *inode, struct file *filp, const char *buf,
                size_t count, loff_t *f_pos)
{
   int retval = count;
   unsigned long address = lcd_base + (MINOR(inode->i_rdev)&0x0f);
   unsigned char *kbuf=kmalloc(count, GFP_KERNEL), *ptr;
   
    if (!kbuf) return -ENOMEM;
    if (copy_from_user(kbuf, buf, count))
       return -EFAULT;
    ptr=kbuf;
    
    while (count--) {
       outb(*(ptr++), address);
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
   int result;
   
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

