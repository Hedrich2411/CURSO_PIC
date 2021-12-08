/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 07 December 2021, 21:06
 */


#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#include "reloj.h"
#include "lcd_pic.h"


void main(void) {
        
    //Pines analogicos como digitales
    ADCON1 = 0x0F;
    TRISD = 0;
    LCD_Init();
    LCD_clear();
    Set_Cursor(1,1);
    LCD_String("HOLA QUE TAL");
    Set_Cursor(2,1);
    LCD_String("COMO ESTAS");
    
    
    while(1){
    
        
    }
    
    
    return;
}
