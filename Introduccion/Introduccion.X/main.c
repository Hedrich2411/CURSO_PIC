/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 07 December 2021, 13:27
 */


#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#define _XTAL_FREQ 8000000UL
//Oscilador 8MHz

void main(void) {
    
    //Pines analogicos como digitales
    ADCON1 = 0x0F;
    //Puerto B como salida
    TRISB = 0;
    
    while(1){
        
        //Encendemos el pin B0
        LATBbits.LATB0 = 1;
        __delay_ms(1000);
        //Apagamos el pin B0
        LATBbits.LATB0 = 0;
        __delay_ms(1000);
        
    }
   
    return;
}
