/*
 * GccApplication1.c
 *
 * Created: 03/09/2022 
 * Author : HOSSAM MOSTAFA
 */ 

/************************ Includes and Macros ************************/
#include "STD.h"
#include "DIO.h"
#include "LED.h"
#include "LCD.h"
#include "TIMER0.h"
#include "TIMER_1.h"
#include "UART.h"
#include "ULTRASONIC.h"


#define F_CPU 16000000UL
#include <util/delay.h>

#define PRESSED				1
#define NOT_PRESSED			0

#define MAIN_MOTOR_PIN_1		GPIO_C,GPIO_PIN_5
#define MAIN_MOTOR_PIN_2		GPIO_C,GPIO_PIN_7
#define RIGHT_MOTOR				GPIO_C,GPIO_PIN_4
#define LEFT_MOTOR 				GPIO_C,GPIO_PIN_6

/************************ Global Variables ************************/

u8 flag_Motor_State_FW	  = PRESSED ;
u8 flag_Motor_State_BW	  = PRESSED ;
u8 flag_control_Blink_Led = PRESSED ;
u8 flag_control_CCS		  = PRESSED;
u8 Local_u8KeyPressed	  = NOT_PRESSED;

void TIMER_0_EXC(void);

int main(void)
{	
	/***************** Led Init ****************/
	H_LedInit(LIGHT_LED);
	H_LedInit(CCS_LED); 
	
	M_DIOInitPin(MAIN_MOTOR_PIN_1,PIN_OUTPUT);
	M_DIOInitPin(MAIN_MOTOR_PIN_2,PIN_OUTPUT);
	M_DIOInitPin(RIGHT_MOTOR,PIN_OUTPUT);
	M_DIOInitPin(LEFT_MOTOR,PIN_OUTPUT);
	/***************** Lcd Init ******************/
	H_LcdInit();
	H_LCDGoTo(ROW_0,COL_1);
	H_LcdWriteString("STATE :Forward");
	H_LCDGoTo(ROW_1,COL_1);
	H_LcdWriteString("CCS : OFF");
	H_LCDGoTo(ROW_1,COL_10);
	H_LcdWriteString("d=");
	/***************** Uart Init ******************/

	M_UARTInit(UART_Data_Bits_8,UART_Parity_Even,UART_Stop_Bits_1);
	M_UARTSetBaudRate(9600,UART_Speed_Normal);
	
	/***************** Timer 0 Init ******************/

	M_Timer0Init();
	
	/***************** Ultrasonic Init ******************/
	H_UltraInit();

	while(1)
	{	
		Local_u8KeyPressed = M_UARTRecieve();	
		switch(Local_u8KeyPressed)
		{
			//******************************LEDS**************************//

			case'A':
				H_LedTog(LIGHT_LED); // led
				break;
		
			case'Z' : //Buzzer 
				H_LedTog(BUZZER); // Buzzer
				break;		
		
		//****************************** Motor_DIRICTION **************************//

			case 'R' : //Motor_control_Dirction_Right
				M_DIOTogPin(RIGHT_MOTOR);
				M_DIOWritePin(LEFT_MOTOR,PIN_LOW);
				break;			
			
			case 'L': //Motor_control_Dirction_left
				M_DIOTogPin(LEFT_MOTOR);
				M_DIOWritePin(RIGHT_MOTOR,PIN_LOW);
				break;		
		
		//****************************** CCS **************************//
		
		
			case 'F': //Motor_control_Forward_Direction 
				H_LCDGoTo(ROW_0,COL_8);
				H_LcdWriteString("Forward ");
				flag_Motor_State_BW = NOT_PRESSED;
				flag_Motor_State_FW = PRESSED;
				M_DIOWritePin(MAIN_MOTOR_PIN_1,PIN_LOW);
				M_DIOWritePin(MAIN_MOTOR_PIN_2,PIN_HIGH);
				break;
			
			case 'B': // Motor_control_Backward_Direction
				H_LCDGoTo(ROW_0,COL_8);
				H_LcdWriteString("Backward");
				flag_Motor_State_FW = NOT_PRESSED;				
				flag_Motor_State_BW = PRESSED ;
				M_DIOWritePin(MAIN_MOTOR_PIN_1,PIN_HIGH);
				M_DIOWritePin(MAIN_MOTOR_PIN_2,PIN_LOW);	
				break ;
				
		//******************************CCS**************************//

			case 'C' : // control_Blink_Led  
				H_LedTog(CCS_LED);
				if (flag_control_CCS == PRESSED)
				{
					H_LCDGoTo(ROW_1,COL_7);
					H_LcdWriteString("ON ");
					M_Timer0SetTime(200);
					M_Timer0OVFInt(TIMER_0_EXC);
					M_Timer0Start();
				}
				
				else if (flag_control_CCS == NOT_PRESSED)
				{
					H_LCDGoTo(ROW_1,COL_7);
					H_LcdWriteString("OFF");
					M_Timer0Stop();
					M_DIOWritePin(MAIN_MOTOR_PIN_2,PIN_LOW);
					M_DIOWritePin(MAIN_MOTOR_PIN_1,PIN_LOW);
				}
				flag_control_CCS ^= PRESSED ;
			}	
	}
}

void TIMER_0_EXC (void)
{
	H_UltraTrigger();
	H_UltraUltraRissingEdge();
	H_UltraUltraFallingEdge();
	u32 Local_u32_Distance ;
	Local_u32_Distance = H_UltraDistance();
	H_LCDGoTo(ROW_1,COL_12);
	H_LcdWriteString("  ");
	H_LCDGoTo(ROW_1,COL_12);
	H_LcdWriteNumber((fl64)Local_u32_Distance); 
	if (Local_u32_Distance > 5) // if distance greater than 5 m 
	{
		if (flag_Motor_State_BW == PRESSED)
		{
			M_DIOWritePin(MAIN_MOTOR_PIN_1,PIN_HIGH);
			M_DIOWritePin(MAIN_MOTOR_PIN_2,PIN_LOW);
		}
		else if(flag_Motor_State_FW == PRESSED)
		{
			M_DIOWritePin(MAIN_MOTOR_PIN_2,PIN_HIGH);
			M_DIOWritePin(MAIN_MOTOR_PIN_1,PIN_LOW);
		}
	}
	if (Local_u32_Distance <= 5)
	{
		M_DIOWritePin(MAIN_MOTOR_PIN_2,PIN_LOW);
		M_DIOWritePin(MAIN_MOTOR_PIN_1,PIN_LOW);
	}	
}

