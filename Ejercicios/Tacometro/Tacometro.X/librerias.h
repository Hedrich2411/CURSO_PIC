/* 
 * File:   librerias.h
 * Author: Vland
 *
 * Created on 11 December 2021, 20:04
 */

#ifndef LIBRERIAS_H
#define	LIBRERIAS_H

#include <xc.h>
#include <stdio.h>
#include "reloj.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


void config_interrup_cero(bool edge);
void config_interrup_one(bool edge);
void config_interrup_two(bool edge);
void config_all_interrup(bool edge_0, bool edge_1, bool edge_2);

void adc_init(void);
float analogic_read(uint8_t channel);


void USART_init(uint16_t baudrate);
void USART_PutChar(char Ch);
void USART_PutString(char *str);


void pwm_init(bool pwm1, bool pwm2);
void set_duty_cpp1(float duty);
void set_duty_cpp2(float duty);

#endif	/* LIBRERIAS_H */

