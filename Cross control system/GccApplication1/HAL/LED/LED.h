/*
 * LED.h
 *
 * Created: 8/27/2021 5:15:56 PM
 *  Author: HOSSAM MOSTAFA
 */ 

#ifndef LED_H_
#define LED_H_

#include "STD.h"
#include "LED_CFG.h"
#include "DIO.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void H_LedInit (DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx);
void H_LedOn   (DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx);
void H_LedOff  (DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx);
void H_LedTog  (DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx);
void H_LedBlink(DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx);

#define LIGHT_LED			GPIO_C,GPIO_PIN_0
#define CCS_LED				GPIO_C,GPIO_PIN_1

#define BUZZER				GPIO_C,GPIO_PIN_3

#endif /* LED_H_ */