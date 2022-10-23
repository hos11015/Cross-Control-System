/*
 * LED.c
 *
 * Created: 8/27/2021 5:15:56 PM
 *  Author: HOSSAM MOSTAFA
 */ 

#include "LED.h"
void H_LedInit(DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx)
{
	M_DIOInitPin(PORTx,PINx,PIN_OUTPUT);
}
void H_LedOn(DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx)
{
	
	M_DIOWritePin(PORTx,PINx,PIN_HIGH);
}
void H_LedOff(DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx)
{
	M_DIOWritePin(PORTx,PINx,PIN_LOW);
}
void H_LedTog(DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx)
{
	M_DIOTogPin(PORTx,PINx);
}
void H_LedBlink(DIO_PORT_NAME_t PORTx,DIO_PIN_NAME_t PINx)
{
	M_DIOWritePin(PORTx,PINx,PIN_HIGH);
	_delay_ms(50);
	M_DIOWritePin(PORTx,PINx,PIN_LOW);
}

