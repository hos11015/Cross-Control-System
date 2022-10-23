/*
 * UART.h
 *
 * Created: 22/09/2022 02:36:11
 *  Author: HOSSAM MOSTAFA
 */ 


#ifndef UART_H_
#define UART_H_

#include "BIT_MATH.h"
#include "STD.h"
#include "REG.h"
#include "avr/interrupt.h"
#define F_CPU 16000000UL

void (* g_UART_TX_Complete_Ptr) (void) ;
void (* g_UART_RX_Complete_Ptr) (void) ;
void (* g_UART_UDR_Empty_Ptr)	(void) ;

/***** UCSRA Bits*******/

#define RXC		7
#define TXC 	6
#define UDRE 	5
#define FE 		4
#define DOR 	3
#define PE 		2
#define U2X 	1
#define MPCM	0

/***** UCSRB Bits*******/
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/***** UCSRC Bits*******/

#define URSEL   7
#define UMSEL	6
#define UPM1	5
#define UPM0	4
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UCPOL	0


/************ Enums ******************/
typedef enum 
{
	UART_Data_Bits_5 = 0 ,
	UART_Data_Bits_6	 ,
	UART_Data_Bits_7	 ,
	UART_Data_Bits_8	 ,
	UART_Data_Bits_9
}UART_Data_Bits_t;

typedef enum 
{
	UART_Parity_No_Parity = 0 ,
	UART_Parity_Even	  = 2 ,
	UART_Parity_Odd		  = 3
}UART_Parity_t;

typedef enum
{
	UART_Stop_Bits_1 = 0 ,
	UART_Stop_Bits_2		  
}UART_Stop_Bits_t;

typedef enum
{
	UART_Speed_Normal = 0 ,
	UART_Speed_2x
}UART_Speed_t;
/*********** Prototypes ***************/
////////////////////////////////////////////////////////////////
/***************************************************************
*FUNCTION NAME : M_UARTInit
* -> Input : - UART_Data_Bits :	UART_Data_Bits_5
*								UART_Data_Bits_6
*								UART_Data_Bits_7
*								UART_Data_Bits_8
*								UART_Data_Bits_9
*								
*			 - UART_Parity	  : UART_Parity_No_Parity
*			 					UART_Parity_Even	 
*			 					UART_Parity_Odd		 
*			 
*			 - UART_Stop_Bits : UART_Stop_Bits_1
*								UART_Stop_Bits_2
* -> Output : ------		
*
* // Set the Uart no of data bits , no of parity bits and no of stop bits  
*
******************************************************************/
void M_UARTInit(UART_Data_Bits_t UART_Data_Bits ,UART_Parity_t UART_Parity ,UART_Stop_Bits_t UART_Stop_Bits);
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/***************************************************************
*FUNCTION NAME : M_UARTSetBaudRate
* -> Input : - baud_rate	  : baud rate value 	
*							
*			 - UART_Speed	  : UART_Speed_Normal
*			 					UART_Speed_2x
* -> Output : ------
*
* // Set the Uart baud rate value and whether uart run in normal or 2x speed
*
******************************************************************/
void M_UARTSetBaudRate(u32 baud_rate, UART_Speed_t UART_Speed);
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/***************************************************************
*FUNCTION NAME : M_UARTSend
* -> Input : - baud_rate	  : data (the data you want to send)
* -> Output : ------
*
* // Send the data
*
******************************************************************/
void M_UARTSend(u8 data);
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/***************************************************************
*FUNCTION NAME : M_UARTRecieve
* -> Input : ----
* -> Output : data recieved from uart
*
* // Send the data
*
******************************************************************/
u8 M_UARTRecieve(void);
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/***************************************************************
*FUNCTION NAME : M_UARTInitTxCompleteInterrupt
* -> Input	: ----
* -> Output : ----
*
* // decide which action happen when uart Tx complete
*
******************************************************************/
void M_UARTInitTxCompleteInterrupt(void (*UARTInterruptPointerFunction)(void))	;
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/***************************************************************
*FUNCTION NAME : M_UARTInitRxCompleteInterrupt
* -> Input	: ----
* -> Output : ----
*
* // decide which action happen when uart Rx complete
*
******************************************************************/
void M_UARTInitRxCompleteInterrupt(void (*UARTInterruptPointerFunction)(void))	;
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/***************************************************************
*FUNCTION NAME : M_UARTInitUDREmptyInterrupt
* -> Input	: ----
* -> Output : ----
*
* // decide which action happen when UDR (uart data register) is Empty 
*
******************************************************************/
void M_UARTInitUDREmptyInterrupt  (void (*UARTInterruptPointerFunction)(void))	;
////////////////////////////////////////////////////////////////
#endif /* UART_H_ */