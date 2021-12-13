# 1 "pid_control.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "E:/MPLAB/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "pid_control.c" 2

# 1 "./pid_control.h" 1




typedef struct{


    float Kp;
    float Ki;
    float Kd;

    float LimMax;
    float LimMin;

    float integrador;
    float integradorAnterior;
    float errorAnterior;
    float derivador;



    float uT;

}ControladorPID;

void ControladorPID_init(ControladorPID*pid);


float CalculoControlPID(ControladorPID*pid,float referencia,float medicion);
# 2 "pid_control.c" 2


void ControladorPID_init(ControladorPID*pid)
{
    pid->integrador=0.0;
    pid->errorAnterior=0.0;
    pid->derivador=0.0;
    pid->integradorAnterior=0.0;

}


float CalculoControlPID(ControladorPID*pid,float setpoint,float medicion)
{

    float error=setpoint-medicion;
    float proporcional=pid->Kp*error;
    pid->integrador=pid->Ki*error+pid->integradorAnterior;
    pid->derivador=pid->Kd*(error-pid->errorAnterior);
    pid->uT=proporcional+pid->integrador+pid->derivador;

    if(pid->uT>pid->LimMax){

    pid->uT=pid->LimMax;

    }else if(pid->uT<pid->LimMin){

    pid->uT=pid->LimMin;

    }
    pid->integradorAnterior=pid->integrador;
    pid->errorAnterior=error;


    return pid->uT;

}
