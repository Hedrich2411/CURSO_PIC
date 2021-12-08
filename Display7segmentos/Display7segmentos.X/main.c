/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 07 December 2021, 19:37
 */


#include <xc.h>
#include "config.h"
#include <pic18f4550.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000UL
#define UNIDADES LATD
#define DECENAS LATB

//Arreglo para mostrar los numeros 0,1,2,3,4,5,6,7,8,9
uint8_t display_array[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void contador_unidades(uint8_t num_max);
void contador_decimal(uint8_t num_max);

void main(void) {
    
    //Pines analogicos como digitales
    ADCON1 = 0x0F;
    //Puertos como salida
    TRISB = 0;
    TRISD = 0;
   
    
    while(1){
    
        contador_decimal(99);
       
    
    }
    
    return;
}

void contador_unidades(uint8_t num_max){

    for(int i=0;i<=num_max;i++){
    
        UNIDADES = display_array[i];
        __delay_ms(1000);
    }
}

void contador_decimal(uint8_t num_max){

    uint8_t decenas = num_max/10;
	uint8_t unidades = num_max%10;
    
    for(int d=0;d<=decenas;d++){
        
        DECENAS = display_array[d];
        
        for(int u=0;u<=unidades;u++){
            
            UNIDADES = display_array[u];
            __delay_ms(500);
        }
    }

}