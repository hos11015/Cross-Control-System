/*
 * LCD.c
 *
 * Created : 19/04/2022 
 * Version : 2
 * Author  : HOSSAM MOSTAFA
 */ 

#ifndef LCD_H_
#define LCD_H_

/**********INCLUDES************************************/

#include "STD.h"
#include "DIO.h"
#include "REG.h"
#include "LCD_CFG.h"
# define F_CPU 16000000UL
#include <util/delay.h>

/**************************** PROTOTYPES *********************************/

void H_LcdInit(void);
void H_LcdWriteChar(u8);
void H_LcdClear(void);
void H_LcdWriteCommand(u8);
void H_LcdWriteString(u8 *);
void H_LcdWriteNumber(fl64);
void H_LCDGoTo(u8 , u8);
/**************************** MACROS ************************************/

#define _4_BIT_MODE					    4
#define _8_BIT_MODE					    8
									   
#define ROW_0_HOME					   0x80
#define ROW_1_HOME					   0xC0

#define ROW_0							0
#define ROW_1							1
										
#define COL_0							0
#define COL_1							1
#define COL_2							2
#define COL_3							3
#define COL_4							4
#define COL_5							5
#define COL_6							6
#define COL_7							7
#define COL_8							8
#define COL_9							9
#define COL_10							10
#define COL_11							11
#define COL_12							12
#define COL_13							13
#define COL_14							14
#define COL_15							15

#if defined(KIT)

#define ROW_2							2
#define ROW_3							3

#define COL_16							16
#define COL_17							17
#define COL_18							18
#define COL_19							19

#define ROW_2_HOME					   0x94
#define ROW_3_HOME					   0xD4

#endif

#define  _8_BIT_MODE_COMMAND					 0x38
#define  DISPLAY_ON_CURSOR_OFF_COMMAND		     0X0C
#define  RETURN_HOME_COMMAND					 0x02
#define  DISPLAY_LEFT_TO_RIGHT_COMMAND			 0X06
#define  CLEAR_LCD_COMMAND						 0X01
#define  _4_BIT_MODE_COMMAND_1					 0x33
#define  _4_BIT_MODE_COMMAND_2					 0x32
#define  _4_BIT_MODE_COMMAND_3					 0x28

/***************************************************/


#endif /* LCD_H_ */