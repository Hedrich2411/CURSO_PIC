

#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#include <stdint.h>

#define _XTAL_FREQ 8000000UL
//Oscilador 8MHz 


void Timer_init(void);

void main(void) {
    
    //Pines analogicos como digitales
    ADCON1 = 0x0F;
    //Puerto B como salida
    TRISB = 0;
    Timer_init();
    while(1){
    
        
    }
    
    
    return;
}

//Timer 0 

void Timer_init(void){
    
    //Timer inicialmente apagado
    T0CONbits.TMR0ON = 0; 
    //Modo 16 bits
    T0CONbits.T08BIT = 0;
    //Modo temporizador
    T0CONbits.T0CS = 0;
    //Sin preescaler
    T0CONbits.PSA = 1;
    //Cargamos para 5ms
    TMR0 = 0xD8F0;
    //Habilita interrupciones de perifericos
    INTCONbits.PEIE = 1;
    //Habilita interrupciones globales
    INTCONbits.GIE = 1;
    //Habilitar interrupcion del timer 0
    INTCONbits.TMR0IE = 1;
    //Timer habilitado
    T0CONbits.TMR0ON = 1;
    
}

void __interrupt() ISR(){

    if(INTCONbits.TMR0IF == 1){
        
        LATBbits.LATB0 = ~ LATBbits.LATB0;
        
        TMR0 = 0xD8F0;
        INTCONbits.TMR0IF = 0;
        
    }


}


