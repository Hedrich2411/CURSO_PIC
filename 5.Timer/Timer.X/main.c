

#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#include <stdint.h>

#define _XTAL_FREQ 8000000UL
//Oscilador 8MHz 


void timer_ms_delay(uint16_t tiempo);
void Timer_init(void);

void main(void) {
    
    //Pines analogicos como digitales
    ADCON1 = 0x0F;
    //Puerto B como salida
    TRISB = 0;
    Timer_init();
    while(1){
    
        LATBbits.LATB0 = 1;
        timer_ms_delay(1000);
        LATBbits.LATB0 = 0;
        timer_ms_delay(1000);
    }
    
    
    return;
}

//Timer 0 

void Timer_init(void){

    T0CON	 = 0x42;
    T0CONbits.TMR0ON = 0; //Timer apagado
    TMR0L	 = 0x06;    //1 ms 
    INTCONbits.TMR0IF = 0;

  
}

void timer_ms_delay(uint16_t tiempo){
    
    //Creamos una funcion para cualquier tiempo.
    uint16_t n;
    
    for(n=1;n<=tiempo;n++){
        LATBbits.LATB1 = ~LATBbits.LATB1;
        T0CONbits.TMR0ON = 1;
        while (INTCONbits.TMR0IF == 0){}
        T0CONbits.TMR0ON = 0;
        INTCONbits.TMR0IF = 0;
   
        }
}