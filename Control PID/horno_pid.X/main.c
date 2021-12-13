/*
 * File:   main.c
 * Author: Vland
 *
 * Created on 11 December 2021, 20:01
 */


#include <xc.h>
#include "librerias.h"
#include "pid_control.h"


/********MACROS********/
#define PID_KP  2.0
#define PID_KI  0.02377
#define PID_KD  0.0
#define PID_LIM_MIN  0.0
#define PID_LIM_MAX  100.0
/***********************/


float referencia=60.0;
float valor,U;
char cadena[20];

void main(void) {
    
    //Pin AN0 y AN1 como analogico
    //Consultar datasheet
    ADCON1bits.PCFG = 0xE;
    TRISAbits.RA0 = 1;
    TRISC = 0;
    
    
    adc_init();
    USART_init(9600);
    pwm_init(true,false);
    
    ControladorPID PIDmotor={PID_KP, PID_KI, PID_KD,PID_LIM_MAX,PID_LIM_MIN};
    ControladorPID_init(&PIDmotor);
    
    while(1){
        
        valor = (analogic_read(0)*(500))/(1023);
        U = CalculoControlPID(&PIDmotor,referencia,valor);
        set_duty_cpp1(U);
        __delay_ms(100);
        sprintf(cadena,"setpoint: %.2f  ",(double)referencia);
        USART_PutString(cadena);
        sprintf(cadena,"temp: %.2f\r",(double)valor);
        USART_PutString(cadena);
    
    }
    
    return;
}
