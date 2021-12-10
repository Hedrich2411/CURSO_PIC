/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 08 December 2021, 11:25
 */


#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#include <stdint.h>
#include <stdbool.h>
#define _XTAL_FREQ 8000000UL
//Oscilador 8MHz

void config_interrup_cero(bool edge);
void config_interrup_one(bool edge);
void config_interrup_two(bool edge);
void config_all_interrup(bool edge_0, bool edge_1, bool edge_2);

void main(void) {
    
    //Pines analogicos como digitales
    ADCON1 = 0x0F;
    //Puerto B como salida
    TRISD = 0;
    config_all_interrup(true,true,true);
    
    while(1){
    
        
        
    
    }
    
    
    return;
}

void config_interrup_cero(bool edge){
    
    TRISBbits.RB0 = 1;      //Pin como entrada
    INTCON2bits.INTEDG0 = edge; //configuracion del flanco
    INTCONbits.INT0IF = 0;  //Bandera en 0
    INTCONbits.INT0IE = 1; //Habilita interrupcion int 0
    INTCONbits.GIE = 1;    //Habilita interrupciones globales
}

void config_interrup_one(bool edge){
    
    TRISBbits.RB1 = 1;      //Pin como entrada
    INTCON2bits.INTEDG1 = edge; //configuracion del flanco
    INTCON3bits.INT1IF = 0;  //Bandera en 0
    INTCON3bits.INT1IE = 1; //Habilita interrupcion int1
    INTCONbits.GIE = 1;    //Habilita interrupciones globales
}

void config_interrup_two(bool edge){
    
    TRISBbits.RB2 = 1;      //Pin como entrada
    INTCON2bits.INTEDG2 = edge; //configuracion del flanco
    INTCON3bits.INT2IF = 0;  //Bandera en 0
    INTCON3bits.INT2IE = 1; //Habilita interrupcion int2
    INTCONbits.GIE = 1;    //Habilita interrupciones globales
}



void config_all_interrup(bool edge_0, bool edge_1, bool edge_2){
    
    config_interrup_cero(edge_0);
    config_interrup_one(edge_1);
    config_interrup_two(edge_2);
    
}


void __interrupt() ISR(){
    
    //Sondeo de interrupciones
    if(INTCONbits.INT0IF == 1){
        
        LATDbits.LATD0 = ~LATDbits.LATD0;
        INTCONbits.INT0IF = 0;
    }else if (INTCON3bits.INT1IF == 1){
        
        LATDbits.LATD1 = ~LATDbits.LATD1;
        INTCON3bits.INT1IF = 0;
    }else if (INTCON3bits.INT2IF == 1){
        
        LATDbits.LATD2 = ~LATDbits.LATD2;
        INTCON3bits.INT2IF = 0;
    }
}