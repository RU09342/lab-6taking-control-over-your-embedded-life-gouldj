#include "msp430.h"
#include "in430.h"
//#define LCD_RS P2OUT_bit.P6
//#define LCD_EN P2OUT_bit.P7
#define LCD_DATA P1OUT
#define LCD_STROBE() ((P2OUT|=BIT7),(P2OUT&=~BIT7))
#define nop() asm("nop")
//#define LCD_STROBE() asm("nop")

extern void lcd_write(unsigned char); // LCD ye komut g�ndermeye yarar
extern void lcd_temizle(void); // LCD ekran� temizler
extern void lcd_puts(const char *); // LCD ye string ifade yazar
extern void lcd_goto(unsigned char, unsigned char);// LCD de sat�r ve st�n olarak istenilen yere gider
extern void lcd_init(void); // LCD ba�lang�� ayarlar� yap�l�r
extern void lcd_putch(char); // LCD ye tek karakter yazmak i�in kullan�l�r.
extern void delay_ms(unsigned int); // Ge�ici delay