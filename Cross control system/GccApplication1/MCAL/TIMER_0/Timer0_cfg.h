/*
 * Timer0_cfg.h
 *
 * Created: 13/09/2022 01:05:35
 *  Author: HOSSAM MOSTAFA
 */ 


#ifndef TIMER0_CFG_H_
#define TIMER0_CFG_H_

///////////////////////////// Timer 0 /////////////////////////////
/************************************************
* TIMER_MODE options :	-TIMER0_NORMAL_MODE
						-TIMER0_CTC_MODE
						-TIMER0_FAST_PWM_MODE
						-TIMER0_PHASE_CORRECT_PWM_MODE
************************************************/			

#define TIMER0_MODE					TIMER0_NORMAL_MODE

/************************************************
* PRESCALER_VALUE options :	-TIMER0_NO_PRESCALER	 
							-TIMER0_PRESCALER_8     
							-TIMER0_PRESCALER_64	
							-TIMER0_PRESCALER_256	
							-TIMER0_PRESCALER_1024	
							-TIMER0_EX_CLK_FALL_EDGE
							-TIMER0_EX_CLK_RISE_EDGE
************************************************/			

#define TIMER0_PRESCALER_VALUE				TIMER0_PRESCALER_1024

/************************************************
* OC0_OUTPUT_MODE options :	-TIMER0_NON_INVERTING_MODE	 
							-TIMER0_INVERTING_MODE     
************************************************/
#define TIMER0_OC0_OUTPUT_MODE					TIMER0_INVERTING_MODE

///////////////////////////////////////////////////////////////////////////
/**************************** Timer 2 *************************************/
//////////////////////////////////////////////////////////////////////////////

/************************************************
* TIMER_MODE options :	-TIMER2_NORMAL_MODE
						-TIMER2_CTC_MODE
						-TIMER2_FAST_PWM_MODE
						-TIMER2_PHASE_CORRECT_PWM_MODE
************************************************/			

#define TIMER2_MODE					TIMER2_NORMAL_MODE

/************************************************
* PRESCALER_VALUE options :	-TIMER2_NO_PRESCALER	 
							-TIMER2_PRESCALER_8     
							-TIMER2_PRESCALER_64	
							-TIMER2_PRESCALER_256	
							-TIMER2_PRESCALER_1024	
							-TIMER2_EX_CLK_FALL_EDGE
							-TIMER2_EX_CLK_RISE_EDGE
************************************************/			

#define TIMER2_PRESCALER_VALUE				TIMER2_PRESCALER_1024

/************************************************
* OC0_OUTPUT_MODE options :	-TIMER2_NON_INVERTING_MODE	 
							-TIMER2_INVERTING_MODE     
************************************************/
#define TIMER2_OC0_OUTPUT_MODE					TIMER2_INVERTING_MODE

#define TIMER0_PRESCALER_D_F					1024
#define F_OSC									16

#endif /* TIMER0_CFG_H_ */