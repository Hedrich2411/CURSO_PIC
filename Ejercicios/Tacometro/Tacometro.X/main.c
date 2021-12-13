/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 12 December 2021, 18:30
 */


/*  COMENTARIO
    
El calculo de RPM no es exacto porque estamos usando delays , esto se soluciona 
haciendo uso de los timers y se aplicara en nuestro control PID de velocidad.
 
 */


#include <xc.h>
#include "librerias.h"

volatile float pulses = 0;
float RPM = 0,velocidad;
char cadena[15];

void main(void) {
    
    //PinA AN0 como analogico
    ADCON1 = 0x0E;
    TRISC = 0;
    TRISAbits.RA0 = 1;
    
    
    config_interrup_cero(true);
    USART_init(9600);
    adc_init();
    pwm_init(true,false);
    
    
    while(1){
        
        pulses = 0;
        __delay_ms(1000); //Tiempo de muestreo(mejorable con timer)
        //Calculo de RPM
        RPM = (60*pulses)/100; // 100 pulsos-> una revolucion 
        velocidad = (analogic_read(0)*100)/1023; //Lectura del adc
        set_duty_cpp1(velocidad);
        sprintf(cadena,"Rpm : %.0f\r",(double)RPM);
        USART_PutString(cadena);
       
    }
    
    return;
}


void __interrupt() ISR(){
    
    //Sondeo de interrupciones
    if(INTCONbits.INT0IF == 1){  
        pulses++; //Aumentamos pulsos
        INTCONbits.INT0IF = 0;
    }
    
}