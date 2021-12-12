/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 11 December 2021, 11:23
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>
#include <stdbool.h>

#define _XTAL_FREQ 8000000UL

volatile char caracter; 


void USART_init(uint16_t baudrate);
void USART_PutChar(char Ch);
void USART_PutString(char *str);

void main(void) {
    //Pines analogicos como digitales
    ADCON1 = 0x0F;
    
    USART_init(9600);//9600 baudios
    
    while(1){
    
            
        if(caracter=='A'){
            USART_PutString("CARACTER A \r");
            
        }else if(caracter == 'B'){
            USART_PutString("CARACTER B \r");
        }
        
        __delay_ms(500);
        

        
    }
    
    return;
}

void USART_init(uint16_t baudrate){

    //Calculo de registro SPBRG
    SPBRG = (unsigned char)(((_XTAL_FREQ/baudrate)/64)-1);
    
    TXSTAbits.BRGH = 0; //Baja velocidad
    TXSTAbits.SYNC = 0; //Modo asincrono
    RCSTAbits.SPEN = 1; //Habilitar comunicacion serial
    
    TXSTAbits.TX9 = 0; //modo 8 bits 
    TXSTAbits.TXEN = 1; //Habilita transmisión
    RCSTAbits.RC9 = 0; //modo 8 bits
    RCSTAbits.CREN = 1; //Habilita recepciones
    
    INTCONbits.GIE=1;	// Interrupciones globales habilitada
    INTCONbits.PEIE=1;	//Habilita interrupcion de perifericos
    PIE1bits.RCIE=1;	//Habilita interrupcion-recepcion
    
}
void USART_PutChar(char Ch){
    while (TXSTAbits.TRMT == 0);
    TXREG =Ch;
}


void USART_PutString(char *str){
    
    while (*str)
        USART_PutChar(*str++);
    
}

void __interrupt() ISR(){
    
    //Sondeo de interrupciones
    if(PIR1bits.RC1IF == 1){
        
        caracter = RCREG;
        
        PIR1bits.RC1IF = 0;
    }
   
}