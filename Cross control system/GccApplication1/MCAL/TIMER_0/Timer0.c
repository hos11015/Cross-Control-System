/*
 * Timer0.c
 *
 * Created: 12/09/2022 12:54:47
 *  Author: HOSSAM MOSTAFA
 */ 

#include "Timer0.h"

/************************************************ Global Variables *******************************************/
u32 g_No_OfV_Timer0 = 0; 
u32 g_no_cmp_Timer0 = 0;

u32 g_No_OfV_Timer2 = 0;
u32 g_no_cmp_Timer2 = 0;

/************************************************** Timer 0 ***************************************************/
void M_Timer0Init(void)
{
	#if TIMER_MODE == NORMAL_MODE
	
		CLR_BIT(TCCR0,6);
		CLR_BIT(TCCR0,3);
		
	#elif TIMER_MODE == CTC_MODE

		SET_BIT(TCCR0,6);
		CLR_BIT(TCCR0,3);
	
	#elif TIMER_MODE == FAST_PWM_MODE

		SET_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);

	#elif TIMER_MODE == PHASE_CORRECT_PWM_MODE

		CLR_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);		
		
	#endif				
}

void M_Timer0Start(void)
{
	// Set Prescler value
	MASK_REG(TCCR0,TIMER0_PRESCALER_VALUE);     
	#if		TIMER0_MODE == TIMER0_NORMAL_MODE
		    // OVF Int is enable
			SET_BIT(TIMSK,0);
			// Enable global Int			      
			sei();						
			
	#elif   TIMER0_MODE == TIMER0_CTC_MODE
			// CTC Int is enabled
			SET_BIT(TIMSK,1); 			
			// Enable global Int
			sei();						
	#endif		
}

void M_Timer0SetTime(u32 l_Time_Req)
{
	// in Micro sec
	u32 l_Tick_Time    = TIMER0_PRESCALER_D_F/F_OSC			   ; 
	u32 l_total_ticks  = (l_Time_Req * 1000) / l_Tick_Time	   ;
	#if TIMER0_MODE == TIMER0_NORMAL_MODE
		g_No_OfV_Timer0		   = l_total_ticks / 256		   ;
		u8 l_rem_OVF_Timer0	   = l_total_ticks % 256		   ;
		if(l_rem_OVF_Timer0 != 0 )
		{
			TCNT0 = 255 - l_rem_OVF_Timer0 ;
			g_No_OfV_Timer0 ++;
		}
	
	#elif TIMER0_MODE == TIMER0_CTC_MODE
		u8 divison_factor = 255 ;
		while (l_total_ticks % divison_factor != 0)
		{
			divison_factor --;
		}
		g_no_cmp_Timer0 = l_total_ticks / divison_factor ;
		OCR0     = divison_factor ;
	#endif
}

void M_Timer0Stop(void)
{
	MASK_REG(TCCR0,TIMER0_STOP);
	
	#if		TIMER_MODE == NORMAL_MODE
				
			CLR_BIT(TIMSK,0);	//OVF Int is disabled
				
	#elif   TIMER_MODE == CTC_MODE
			
			CLR_BIT(TIMSK,1);	//CTC Int is disabled
	#endif
}


void M_Timer0PWMInit(void)
{
	M_Timer0Init();	
}

void M_Timer0PWMStart(u8 u8_duty_cycle)
{
	#if OC0_OUTPUT_MODE == INVERTING_MODE
		// SELECT Inverting Mode
		SET_BIT(TCCR0,5);
		SET_BIT(TCCR0,4);
		#if TIMER_MODE == FAST_PWM_MODE
			OCR0 = 255 -((u8_duty_cycle * 256 ) / 100) - 1 ;
		#elif TIMER_MODE == PHASE_CORRECT_PWM_MODE
			OCR0 = 255 - ((u8_duty_cycle * 255) / 100)  ;
		#endif
	#elif OC0_OUTPUT_MODE == NON_INVERTING_MODE
		// SELECT NON_Inverting Mode
		SET_BIT(TCCR0,5);
		CLR_BIT(TCCR0,4);
		#if TIMER_MODE == FAST_PWM_MODE
			OCR0 = ((u8_duty_cycle * 256 ) / 100) - 1 ;
		#elif TIMER_MODE == PHASE_CORRECT_PWM_MODE
			OCR0 = (u8_duty_cycle *255 / 100) ;
		#endif
	#endif
	MASK_REG(TCCR0,TIMER0_PRESCALER_VALUE);    // Set Prescler value
}

void M_Timer0OVFInt(void (*Timer0_OVF_Call_Back)(void))
{
	g_Timer0_OVF_Call_Back = Timer0_OVF_Call_Back ;
}

ISR(TIMER0_OVF_vect)
{
	static u32 count = 0;
	count ++ ;
	if(count == g_No_OfV_Timer0 )
	{
		g_Timer0_OVF_Call_Back();
		count = 0;
	}
}

ISR(TIMER0_COMP_vect)
{
	g_Timer0_CTC_Call_Back();
}

/**************************************************** Timer 2 ************************************/

void M_Timer2Init(void)
{
	#if TIMER2_MODE == TIMER2_NORMAL_MODE
	
	CLR_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);
	
	#elif TIMER2_MODE == TIMER2_CTC_MODE

	SET_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);
	
	#elif TIMER2_MODE == TIMER2_FAST_PWM_MODE

	SET_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);

	#elif TIMER2_MODE == TIMER2_PHASE_CORRECT_PWM_MODE

	CLR_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);
	
	#endif
}

void M_Timer2Start(void)
{
	MASK_REG(TCCR2,TIMER2_PRESCALER_VALUE);    // Set Prescler value
	#if		TIMER2_MODE == TIMER2_NORMAL_MODE
	
	SET_BIT(TIMSK,6);			// OVF Int is enable
	sei();						// Enable global Int
	
	#elif   TIMER2_MODE == TIMER2_CTC_MODE
	
	SET_BIT(TIMSK,7); 			// CTC Int is enabled
	sei();						// Enable global Int
	#endif
}

void M_Timer2SetTime(u32 l_Time_Req)
{
	u32 l_Tick_Time    = 1024/16			   ; // in Micro sec
	u32 l_total_ticks  = (l_Time_Req * 1000) / l_Tick_Time ;
	#if TIMER2_MODE == TIMER2_NORMAL_MODE
	g_No_OfV_Timer2		   = l_total_ticks / 256			   ;
	u8 l_rem_OVF_Timer2	   = l_total_ticks % 256			   ;
	if(l_rem_OVF_Timer2 != 0 )
	{
		TCNT2 = 255 - l_rem_OVF_Timer2 ;
		g_No_OfV_Timer2 ++;
	}
	
	#elif TIMER2_MODE == TIMER2_CTC_MODE
	u8 divison_factor = 255 ;
	while (l_total_ticks % divison_factor != 0)
	{
		divison_factor --;
	}
	g_no_cmp = l_total_ticks / divison_factor ;
	OCR2     = divison_factor ;
	#endif
}

void M_Timer2Stop(void)
{
	MASK_REG(TCCR2,TIMER2_STOP);
	
	#if		TIMER2_MODE == TIMER2_NORMAL_MODE
	
	CLR_BIT(TIMSK,0);	//OVF Int is disabled
	
	#elif   TIMER2_MODE == TIMER2_CTC_MODE
	
	CLR_BIT(TIMSK,1);	//CTC Int is disabled
	#endif
}


void M_Timer2PWMInit(void)
{
	M_Timer2Init();
}

void M_Timer2PWMStart(u8 u8_duty_cycle)
{
	#if OC0_OUTPUT_MODE == TIMER2_INVERTING_MODE
		// SELECT Inverting Mode
		SET_BIT(TCCR2,5);
		SET_BIT(TCCR2,4);
		#if TIMER2_MODE == TIMER2_FAST_PWM_MODE
		OCR2 = 255 -((u8_duty_cycle * 256 ) / 100) - 1 ;
		#elif TIMER2_MODE == TIMER2_PHASE_CORRECT_PWM_MODE
		OCR2 = 255 - ((u8_duty_cycle * 255) / 100)  ;
		#endif
	#elif TIMER2_OC0_OUTPUT_MODE == TIMER2_NON_INVERTING_MODE
		// SELECT NON_Inverting Mode
		SET_BIT(TCCR2,5);
		CLR_BIT(TCCR2,4);
		#if TIMER2_MODE == TIMER2_FAST_PWM_MODE
		OCR0 = ((u8_duty_cycle * 256 ) / 100) - 1 ;
		#elif TIMER2_MODE == TIMER2_PHASE_CORRECT_PWM_MODE
		OCR0 = (u8_duty_cycle *255 / 100) ;
		#endif
	#endif
	MASK_REG(TCCR2,TIMER2_PRESCALER_VALUE);    // Set Prescler value
}


void M_Timer2OVFInt(void (*Timer2_OVF_Call_Back)(void))
{
	g_Timer2_OVF_Call_Back = Timer2_OVF_Call_Back ;
}

ISR(TIMER2_OVF_vect)
{
	static u32 count = 0;
	count ++ ;
	if(count == g_No_OfV_Timer2 )
	{
	g_Timer2_OVF_Call_Back();
	count = 0;
	}
}
ISR(TIMER2_COMP_vect)
{
	g_Timer2_CTC_Call_Back();
}



