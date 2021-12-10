 
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> 
#include "reloj.h"

#define LCD_DATA LATD
#define LCD_CONTROL LATD
#define RS_pin 4
#define E_pin 5
#define D4 0
#define D5 1
#define D6 2
#define D7 3


void LCD_Init(void);
void LCD_Comand(unsigned char cmd);
void LCD_Caracter(unsigned char data);
void LCD_Data(unsigned char Data);
void LCD_String(const char *caden);
void Set_Cursor(unsigned char x,unsigned char y);
void LCD_clear(void);



#endif	/* XC_HEADER_TEMPLATE_H */

