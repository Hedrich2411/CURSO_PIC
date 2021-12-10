

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
    
    
    }
    
    
    return;
}
