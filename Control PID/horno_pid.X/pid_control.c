
#include "pid_control.h"

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