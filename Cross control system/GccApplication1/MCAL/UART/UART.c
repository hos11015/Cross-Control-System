/*
 * UART.c
 *
 * Created: 22/09/2022 02:35:35
 *  Author: HOSSAM MOSTAFA
 */ 
#include "UART.h"

void M_UARTInit(UART_Data_Bits_t UART_Data_Bits ,UART_Parity_t UART_Parity ,UART_Stop_Bits_t UART_Stop_Bits)
{
	/* To Select to use UCSRC instead of URBH */
	SET_BIT(UCSRC,URSEL);
	
	/* Asynch mode */
	CLR_BIT(UCSRC,UMSEL);
	
	if(UART_Data_Bits == UART_Data_Bits_5)
	{
		/* 5 bit data frame */
		CLR_BIT(UCSRB,UCSZ2);
		CLR_BIT(UCSRC,UCSZ1);
		CLR_BIT(UCSRC,UCSZ0);	
	}
	else if(UART_Data_Bits == UART_Data_Bits_6)
	{
		/* 6 bit data frame */
		CLR_BIT(UCSRB,UCSZ2);
		CLR_BIT(UCSRC,UCSZ1);
		SET_BIT(UCSRC,UCSZ0);
	}
	else if(UART_Data_Bits == UART_Data_Bits_7)
	{
		/* 7 bit data frame */
		CLR_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC,UCSZ1);
		CLR_BIT(UCSRC,UCSZ0);
	}
	else if(UART_Data_Bits == UART_Data_Bits_8)
	{
		/* 8 bit data frame */
		CLR_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC,UCSZ1);
		SET_BIT(UCSRC,UCSZ0);
	}
	else if(UART_Data_Bits == UART_Data_Bits_9)
	{
		/* 9 bit data frame */
		SET_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC,UCSZ1);
		SET_BIT(UCSRC,UCSZ0);
	}		

	/* parity Bits */
	MASK_REG(UCSRC,(UART_Parity<<4));

	/* stop bits */
	
	MASK_REG(UCSRC,(UART_Stop_Bits<<USBS));
	
	/* Enable Reciever */
	SET_BIT(UCSRB,RXEN);
	
	/* Enable Transmitter */
	SET_BIT(UCSRB,TXEN);
}
void M_UARTSetBaudRate(u32 baud_rate, UART_Speed_t UART_Speed)
{
	/* To Select to use URBH instead of UCSRC */
	SET_BIT(UCSRC,URSEL);
	if(UART_Speed == UART_Speed_Normal)
	{
		UBR = ( F_CPU / (u32)(16*baud_rate) ) -1;
	}
	else if(UART_Speed == UART_Speed_2x)
	{
		UBR = ( F_CPU / (u32)(8*baud_rate) ) -1	;	
	}
} 
void M_UARTSend(u8 data)
{
	UDR = data ;
	while(GET_BIT(UCSRA,TXC) == 0);
}

u8 M_UARTRecieve(void)
{
	while(GET_BIT(UCSRA,RXC)==0);
	return UDR ;
}

void M_UARTInitTxCompleteInterrupt(void (*UARTInterruptPointerFunction)(void))
{
	SET_BIT(UCSRB,TXCIE); // Trnasmit complete INT Enable
	sei();
	g_UART_TX_Complete_Ptr = UARTInterruptPointerFunction ;
}
void M_UARTInitRxCompleteInterrupt(void (*UARTInterruptPointerFunction)(void))
{
	SET_BIT(UCSRB,RXCIE); // Recieve complete INT Enable
	sei();
	g_UART_RX_Complete_Ptr = UARTInterruptPointerFunction ;
}
void M_UARTInitUDREmptyInterrupt(void (*UARTInterruptPointerFunction)(void))
{
	SET_BIT(UCSRB,UDRIE); // UDR Empty INT Enable
	sei();
	g_UART_UDR_Empty_Ptr = UARTInterruptPointerFunction ;
}

ISR(USART_TXC_vect)
{
	CLR_BIT(UCSRA,UDRE);
	g_UART_TX_Complete_Ptr();
}

ISR(USART_RXC_vect)
{
	g_UART_RX_Complete_Ptr() ;
}

ISR(USART_UDRE_vect)
{
	g_UART_UDR_Empty_Ptr();
}