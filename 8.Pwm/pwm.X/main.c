/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 11 December 2021, 21:10
 */


#include <xc.h>
#include "config.h"
#include <stdbool.h>

#define _XTAL_FREQ 8000000UL


void pwm_init(bool pwm1, bool pwm2);
void set_duty_cpp1(float duty);
void set_duty_cpp2(float duty);


void main(void) {
    
    //Pines analogicos como digitales
    ADCON1 = 0x0F;
    //Puerto C como salida
    TRISC = 0;
    
    pwm_init(true,true);
    
    while(1){
        
        set_duty_cpp1(50);
        set_duty_cpp2(50);
        
    }
    
    return;
}

void pwm_init(bool pwm1, bool pwm2){
    
    /*Frecuencia de señal pwm->PR2
     
     PR2 = (FOSC/(Fpwm*4*TimerPrescaler))-1
     
     */
    PR2 = 199;//->10KHz 
    
    if (pwm1 == true && pwm2 == true){
    
        CCP1CON = 0x0C;//Modo pwm sin decimales  
        CCPR1L = 0; //Dutycycle 0

        CCP2CON = 0x0C;//Modo pwm sin decimales
        CCPR2L = 0; //Dutycycle 0
        
    }else if(pwm1 == true && pwm2 == false){
        
        CCP1CON = 0x0C;//Modo pwm sin decimales  
        CCPR1L = 0; //Dutycycle 0
        
    }else if(pwm1 == false && pwm2 == true){
   
        CCP2CON = 0x0C;//Modo pwm sin decimales
        CCPR2L = 0; //Dutycycle 0
    }
       
    T2CON = 0;// No Timer preescaler
    TMR2 = 0;//Limpiamos timer 2 inicializacion
    T2CONbits.TMR2ON = 1;//Timer 2 on
}

void set_duty_cpp1(float duty){
    CCPR1L = (unsigned char)((PR2)*(duty/100)); 
    
}

void set_duty_cpp2(float duty){
    CCPR2L = (unsigned char)((PR2)*(duty/100)); 
}