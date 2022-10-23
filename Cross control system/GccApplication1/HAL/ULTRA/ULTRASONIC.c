/*
 * ULTRASONIC.c
 *
 * Created: 27/04/2022 10:49:24 م
 *  Author: HOSSAM MOSTAFA
 */ 
#include "ULTRASONIC_CFG.h"
#include "ULTRASONIC.h"
#include "DIO.h"
#include "STD.h"
#include "BIT_MATH.h"
#include "LCD.h"
#include "REG.h"
#include "LED.h"
#define F_CPU 16000000UL
#include <util/delay.h>

static u16 u16_global_RissingValue = 0;
static u16 u16_global_FallingValue = 0;

void H_UltraInit(void)
{
	//TCCR1A = 0;
	M_DIOInitPin(Trigger,PIN_OUTPUT);
	M_DIOInitPin(Echo,PIN_INPUT);
	/* Clear ICF flag */
	SET_BIT(TIFR,5);     
}
void H_UltraTrigger(void)
{
	M_DIOWritePin(Trigger,PIN_HIGH);
	_delay_ms(50);
	M_DIOWritePin(Trigger,PIN_LOW);
	
}

void H_UltraUltraRissingEdge(void)
{
	// Timer 1 Rising edge, no prescaler , noise canceler
	SET_BIT(TCCR1B,7);
	SET_BIT(TCCR1B,6);
	SET_BIT(TCCR1B,0);
	while ((GET_BIT(TIFR,5)) == 0);
	// Take value of capture register
	u16_global_RissingValue = ICR1;
	// Clear ICF flag  		
	SET_BIT(TIFR,5);						
	
}
void H_UltraUltraFallingEdge(void)
{
	// Timer 1 Faling edge, no prescaler , noise canceler
	SET_BIT(TCCR1B,7);
	CLR_BIT(TCCR1B,6);
	SET_BIT(TCCR1B,0);
	while ((GET_BIT(TIFR,5)) == 0);
	// Take value of capture register
	u16_global_FallingValue = ICR1; 
	/* Clear ICF flag */ 		 
	SET_BIT(TIFR,5);
	TCNT1=0;
	/* Stop the timer */        
	TCCR1B= 0;  		
}

u32  H_UltraDistance(void)
{	
	u32 u32_local_TimeOn = u16_global_FallingValue - u16_global_RissingValue;
	u32 u32_local_Distance = 0;
	u32_local_Distance = ((u32_local_TimeOn * 34600) / (F_CPU*2)); //cpu*2
	return u32_local_Distance ;
}