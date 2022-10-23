/*
 * DIO.c
 *
 * Created: 07/09/2022 18:40:34
 *  Author: HOSSAM MOSTAFA
 */ 

#include "DIO.h"

volatile u8 *reg_dir[4] = {&DDRA,&DDRB,&DDRC,&DDRD};
volatile u8 *reg_data[4] = {&PORTA,&PORTB,&PORTC,&PORTD};
volatile u8 *reg_input[4] = {&PINA,&PINB,&PINC,&PIND};
			 

void M_DIOInitPin(DIO_PORT_NAME_t PORTx , DIO_PIN_NAME_t PINx , u8 Direction)
{
	if(Direction == PIN_OUTPUT)
	{
		SET_BIT(*reg_dir[PORTx],PINx);
	}
	else if(Direction == PIN_INPUT)
	{
		CLR_BIT(*reg_dir[PORTx],PINx);	
	}
}

void M_DIOWritePin(DIO_PORT_NAME_t PORTx , DIO_PIN_NAME_t PINx , u8 Data)
{
	if(Data == PIN_HIGH)
	{
		SET_BIT(*reg_data[PORTx],PINx);
	}
	else if(Data == PIN_LOW)
	{
		CLR_BIT(*reg_data[PORTx],PINx);
	}
}

u8 M_DIOReadPin(DIO_PORT_NAME_t PORTx , DIO_PIN_NAME_t PINx)
{
	return GET_BIT(*reg_input[PORTx],PINx);
}

void M_DIOTogPin(DIO_PORT_NAME_t PORTx , DIO_PIN_NAME_t PINx)
{
		TOG_BIT(*reg_data[PORTx],PINx);
}

void M_DIOInitPORT(DIO_PORT_NAME_t PORTx,u8 Direction)
{
	if(Direction == PORT_OUTPUT)
	{
		SET_REG(*reg_dir[PORTx]);
	}
	else if(Direction == PORT_INPUT)
	{
		CLR_REG(*reg_dir[PORTx]);
	}
}

void M_DIOWritePORT(DIO_PORT_NAME_t PORTx , u8 Data)
{
	if(Data == PORT_HIGH)
	{
		SET_REG(*reg_data[PORTx]);
	}
	else if(Data == PORT_LOW)
	{
		CLR_REG(*reg_data[PORTx]);
	}
}

u8 M_DIOReadPORT(DIO_PORT_NAME_t PORTx)
{
	return GET_REG(*reg_input[PORTx]);
}

void M_DIOMaskPORT(DIO_PORT_NAME_t PORTx , u8 Data)
{
	MASK_REG(PORTx,Data);
}

void M_DIOTogPORT(DIO_PORT_NAME_t PORTx)
{
	TOG_REG(*reg_data[PORTx]);

}