/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 10 December 2021, 12:51
 */


#include <xc.h>
#include <pic18f4550.h>
#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "lcd_pic.h"


char str_voltaje[17],str_voltaje2[17];

float voltaje,voltaje2;

void adc_init(void);
float analogic_read(uint8_t channel);

void main(void) {
    
    //Pin AN0 y AN1 como analogico
    //Consultar datasheet
    ADCON1bits.PCFG = 0xD;
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 1;
    
    TRISD = 0;
    adc_init();
    LCD_Init();
    
    while(1){
        //Conversion en voltaje
        voltaje = (analogic_read(0)*5)/1023; 
        voltaje2 = (analogic_read(1)*5)/1023;
        
        sprintf(str_voltaje,"voltaje1: %.1f V",(double)voltaje);
        sprintf(str_voltaje2,"voltaje2: %.1f V",(double)voltaje2);
        
        Set_Cursor(1,2);
        LCD_String(str_voltaje);
        Set_Cursor(2,2);
        LCD_String(str_voltaje2);
 
    }
    
    
    return;
}


void adc_init(void){
    
    ADCON1bits.VCFG = 0; //vss-vdd como referencia
    ADCON0 = 0;
    ADCON2bits.ACQT = 0b011; //Tiempo de adquision = 6TAD
    ADCON2bits.ADCS = 0b101; //Clock conversion FOSC/16
    ADCON2bits.ADFM = 1; // Justificado a la derecha
    
}


float analogic_read(uint8_t channel){
    
    ADCON0 = 0; //Limpiamos el registro
    ADCON0bits.CHS = channel; //Seleccionamos el canal
    ADCON0bits.ADON = 1; //Habilitamos el ADC
    ADCON0bits.GO_DONE = 1; //Inicia la conversion
    
    while(ADCON0bits.GO_DONE == 1);//Bucle hasta que termine la conversion
    ADCON0bits.ADON = 0 ;//Deshabilitamos el ADC
    
    return ADRES; //retornamos el buffer
}


