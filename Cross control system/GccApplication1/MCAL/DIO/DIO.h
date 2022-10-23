/*
 * DIO.h
 *
 * Created: 07/09/2022 18:40:51
 *  Author: HOSSAM MOSTAFA
 */ 

#ifndef DIO_H_
#define DIO_H_

#include "STD.h"
#include "BIT_MATH.h"
#include "REG.h"

typedef enum 
{
	GPIO_A,
	GPIO_B,
	GPIO_C,
	GPIO_D
}DIO_PORT_NAME_t;

typedef enum 
{
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7
}DIO_PIN_NAME_t;

typedef enum
{
	PIN_INPUT ,
	PIN_OUTPUT
}DIO_PIN_DIRECTION_t;

typedef enum 
{
	PIN_LOW ,
	PIN_HIGH
}DIO_PIN_STATE_t;

typedef enum
{
	PORT_LOW ,
	PORT_HIGH = 0xFF
}DIO_PORT_STATE_t;

typedef enum
{
	PORT_INPUT			,
	PORT_OUTPUT = 0xFF
}DIO_PORT_DIRECTION_t;

/***************************************************************
*FUNCTION NAME : M_DIOInitPin
*INPUT  -> PORTx	 : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*		-> PINx		 : GPIO_PIN_0 ........ GPIO_PIN_7
*		-> Direction : PIN_INPUT , PIN_OUTPUT
*
* // decide the direction of the pin
*
******************************************************************/

void M_DIOInitPin(DIO_PORT_NAME_t PORTx , DIO_PIN_NAME_t PINx , u8 Direction);

/////////////***************************************************************//////////////

/***************************************************************
*FUNCTION NAME : M_DIOWritePin
*INPUT  -> PORTx     : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*		-> PINx      : GPIO_PIN_0 ........ GPIO_PIN_7
*		-> Data		 : PIN_INPUT , PIN_OUTPUT
*
* // write the data on the pin
*
******************************************************************/

void M_DIOWritePin(DIO_PORT_NAME_t PORTx , DIO_PIN_NAME_t PINx , u8 Data);

/////////////***************************************************************//////////////

/*****************************************************************
*FUNCTION NAME : M_DIOReadPin
*INPUT  -> PORTx     : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*		-> PINx      : GPIO_PIN_0 ........ GPIO_PIN_7
*
*Return -> pin_state	
* // Read the state of the pin
*
******************************************************************/

u8 M_DIOReadPin(DIO_PORT_NAME_t PORTx , DIO_PIN_NAME_t PINx);
/////////////***************************************************************//////////////

/***************************************************************
*FUNCTION NAME : M_DIOTogPin
*INPUT  -> PORTx	 : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*		-> Direction : PIN_INPUT , PIN_OUTPUT
*
* // decide the direction of the port
*
******************************************************************/

void M_DIOTogPin(DIO_PORT_NAME_t PORTx , DIO_PIN_NAME_t PINx);
/////////////***************************************************************//////////////

/***************************************************************
*FUNCTION NAME : M_DIOInitPort
*INPUT  -> PORTx	 : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*		-> Direction : PORT_INPUT , PORT_OUTPUT
*
* // decide the direction of the port
*
******************************************************************/

void M_DIOInitPORT(DIO_PORT_NAME_t PORTx,u8 Direction);

/////////////***************************************************************//////////////

/***************************************************************
*FUNCTION NAME : M_DIOWritePort
*INPUT  -> PORTx : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*		-> Data  : PORT_HIGH , PORT_LOW
*
* // write the data on the port
*
******************************************************************/

void M_DIOWritePORT(DIO_PORT_NAME_t PORTx , u8 Data);

/////////////***************************************************************//////////////

/*****************************************************************
*FUNCTION NAME : M_DIOReadPort
*INPUT  -> PORTx : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*
*Return -> port_state
* // return the state of the port
*
******************************************************************/

u8	M_DIOReadPORT(DIO_PORT_NAME_t PORTx);

/////////////***************************************************************//////////////

/*****************************************************************
*FUNCTION NAME : M_DIOMaskPORT
*INPUT  -> PORTx     : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*		-> Data      : GPIO_PIN_0 ........ GPIO_PIN_7
*
* // Mask Data to the port
*
******************************************************************/

void M_DIOMaskPORT(DIO_PORT_NAME_t PORTx , u8 Data);

/////////////***************************************************************//////////////

/*****************************************************************
*FUNCTION NAME : M_DIOTogPORT
*INPUT  -> PORTx     : GPIO_A , GPIO_B , GPIO_C , GPIO_D
*
* // Toggle Data in the port
*
******************************************************************/
void M_DIOTogPORT(DIO_PORT_NAME_t PORTx);

#endif /* DIO_H_ */