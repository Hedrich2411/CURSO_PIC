#include "librerias.h"


//////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////

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
///////////////////////////////////////////////////////////

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
    CCPR1L = (unsigned char)((PR2+1)*(duty/100)); 
    
}

void set_duty_cpp2(float duty){
    CCPR2L = (unsigned char)((PR2+1)*(duty/100)); 
}
