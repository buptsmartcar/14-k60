#ifndef __LQ12864_H__
#define __LQ12864_H__

extern void LCD_Init(void);
extern void LCD_CLS(void);
extern void LCD_CLEAR(unsigned char ymin,unsigned char ymax,unsigned char xmin,unsigned char xmax);
extern void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
extern void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
extern void LCD_P14x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
extern void LCD_P16x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
extern void LCD_PrintU16(unsigned char x,unsigned char y,unsigned int num);
extern void LCD_Print(unsigned char x, unsigned char y, unsigned char ch[]);
extern void LCD_PutPixel(unsigned char x,unsigned char y);
extern void LCD_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char gif);
extern void Draw_Logo(void);
//extern void Draw_BMP(); 
extern void Draw_BMP_fullfps();
extern void Draw_BMP_halffps();
extern void LCD_TEST(int i);
extern void LCD_DLY_ms(unsigned int ms);

#endif

