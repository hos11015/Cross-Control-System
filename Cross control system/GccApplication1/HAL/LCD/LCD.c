/*
 * LCD.c
 *
 * Created : 19/04/2022 
 * Version : 2
 * Author  : HOSSAM MOSTAFA
 */ 
#include "LCD.h"

void H_LcdInit(void)
{
	M_DIOInitPin(LCD_RS_PIN,PIN_OUTPUT);
	M_DIOInitPin(LCD_EN_PIN,PIN_OUTPUT);
	#if LCD_MODE == _8_BIT_MODE
	    M_DIOInitPin(LCD_DATA_PIN_0,PIN_OUTPUT);
	    M_DIOInitPin(LCD_DATA_PIN_1,PIN_OUTPUT);
	    M_DIOInitPin(LCD_DATA_PIN_2,PIN_OUTPUT);
	    M_DIOInitPin(LCD_DATA_PIN_3,PIN_OUTPUT);
	    M_DIOInitPin(LCD_DATA_PIN_4,PIN_OUTPUT);
	    M_DIOInitPin(LCD_DATA_PIN_5,PIN_OUTPUT);
	    M_DIOInitPin(LCD_DATA_PIN_6,PIN_OUTPUT);
	    M_DIOInitPin(LCD_DATA_PIN_7,PIN_OUTPUT);
	    		
	    _delay_ms(500);
	    H_LcdWriteCommand(_8_BIT_MODE_COMMAND);
	    H_LcdWriteCommand(DISPLAY_ON_CURSOR_OFF_COMMAND);
	    H_LcdWriteCommand(RETURN_HOME_COMMAND);
	    H_LcdWriteCommand(DISPLAY_LEFT_TO_RIGHT_COMMAND);
	    H_LcdWriteCommand(CLEAR_LCD_COMMAND);
		
	#elif LCD_MODE == _4_BIT_MODE
		M_DIOInitPin(LCD_DATA_PIN_4,PIN_OUTPUT);
		M_DIOInitPin(LCD_DATA_PIN_5,PIN_OUTPUT);
		M_DIOInitPin(LCD_DATA_PIN_6,PIN_OUTPUT);
		M_DIOInitPin(LCD_DATA_PIN_7,PIN_OUTPUT);
		
		_delay_ms(500);
		
		// [COMMAND_1 + COMMAND_2 + COMMAND_3] == 4 BIT MODE
		H_LcdWriteCommand(_4_BIT_MODE_COMMAND_1);
		H_LcdWriteCommand(_4_BIT_MODE_COMMAND_2);
		H_LcdWriteCommand(_4_BIT_MODE_COMMAND_3);
		
		H_LcdWriteCommand(DISPLAY_ON_CURSOR_OFF_COMMAND);
		H_LcdWriteCommand(RETURN_HOME_COMMAND);
		H_LcdWriteCommand(DISPLAY_LEFT_TO_RIGHT_COMMAND);
		H_LcdWriteCommand(CLEAR_LCD_COMMAND);			
	#endif 
}

void H_LcdWriteCommand(u8 command)
{
	//static u8 lcd_counter = 0 ;
	M_DIOWritePin(LCD_RS_PIN,PIN_LOW); // RS = 0 --> command 
	#if LCD_MODE == _8_BIT_MODE
	LCD_DATA_PORT = command; 
	M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
	_delay_ms(1);
	M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
	_delay_ms(5); //?????
/*if(lcd_counter == 16)
{
	H_LCDGoTo(ROW_1,COL_1);
	H_LedInit(R_LED);
	H_LedOn(R_LED);
}*/
	#elif LCD_MODE == _4_BIT_MODE 
	      #if defined(PROTEUS)	 
	      LCD_DATA_PORT = (( (command >> 1) & 0x78) | (LCD_DATA_PORT & 0x87));
	      M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
	      _delay_ms(1);
	      M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
	      _delay_ms(5);
	      LCD_DATA_PORT = (((command << 3) & 0x78)  | (LCD_DATA_PORT & 0x87));
	      M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
	      _delay_ms(1);
	      M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
	      _delay_ms(5);
		  
		  #elif defined(KIT)
		  LCD_DATA_PORT = ((( (command >> 4) & 0x07) | ((command>>3) &0x10)) | (LCD_DATA_PORT & 0xE8));
		  M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
		  _delay_ms(1);
		  M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
		  _delay_ms(5);
		  LCD_DATA_PORT = ( ( (command & 0x07) | ( (command<<1) &0x10) ) | (LCD_DATA_PORT & 0xE8) );
		  M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
		  _delay_ms(1);
		  M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
		  _delay_ms(5);
		  #endif
	#endif
	//lcd_counter ++;
}
void H_LcdWriteChar(u8 character)
{
	M_DIOWritePin(LCD_RS_PIN,PIN_HIGH); // RS = 0 --> DATA

	#if LCD_MODE == _8_BIT_MODE 
		LCD_DATA_PORT = character;
		M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
		_delay_ms(1);
		M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
		_delay_ms(5); //?????
	
		#elif LCD_MODE == _4_BIT_MODE
		#if defined(PROTEUS)
		LCD_DATA_PORT = (( (character >> 1) & 0x78) | (LCD_DATA_PORT & 0x87));
		M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
		_delay_ms(1);
		M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
		_delay_ms(5);
		LCD_DATA_PORT = (((character << 3) & 0x78)  | (LCD_DATA_PORT & 0x87));
		M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
		_delay_ms(1);
		M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
		_delay_ms(5);
		
		#elif defined(KIT)
		LCD_DATA_PORT = ((( (character >> 4) & 0x07) | ((character>>3) &0x10)) | (LCD_DATA_PORT & 0xE8));
		M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
		_delay_ms(1);
		M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
		_delay_ms(5);
		LCD_DATA_PORT = ( ( (character & 0x07) | ( (character<<1) &0x10) ) | (LCD_DATA_PORT & 0xE8) );
		M_DIOWritePin(LCD_EN_PIN,PIN_HIGH);
		_delay_ms(1);
		M_DIOWritePin(LCD_EN_PIN,PIN_LOW);
		_delay_ms(5);
		#endif
	#endif
}

void H_LcdClear(void)
{
	H_LcdWriteCommand(CLEAR_LCD_COMMAND);
}

void H_LcdWriteString(u8 * ptr)
{
	while(*ptr != '\0')
	{
		H_LcdWriteChar(*ptr);
		ptr ++;
	}
}

void H_LcdWriteNumber(fl64 local_number)
{
	s32 s32_local_number_copy = local_number;
	u8 u8_local_arr [10] = {0};
	s8 s8_local_counter = 0;
	if(s32_local_number_copy == 0)
	{
		H_LcdWriteChar('0');
	}
	else if(s32_local_number_copy < 0)
	{
		H_LcdWriteChar('-');
		s32_local_number_copy = s32_local_number_copy * (-1);
	}
	while(s32_local_number_copy != 0)
	{
		u8_local_arr [s8_local_counter] = s32_local_number_copy % 10;
		s8_local_counter++;
		s32_local_number_copy = s32_local_number_copy / 10;
	}
	s8_local_counter--;
	while (s8_local_counter >= 0)
	{
		H_LcdWriteChar(u8_local_arr[s8_local_counter] + '0');
		s8_local_counter--;
	}
}

void H_LCDGoTo(u8 row_position,u8 col_position)
{
	switch (row_position)
	{
		case ROW_0 :
		H_LcdWriteCommand(ROW_0_HOME + col_position);
		break;
		case ROW_1 :
		H_LcdWriteCommand(ROW_1_HOME + col_position);
		break;
		#if defined(KIT)
		case ROW_2 :
		H_LcdWriteCommand(ROW_2_HOME + col_position);
		break;
		case ROW_3 :
		H_LcdWriteCommand(ROW_3_HOME + col_position);
		break;
		#endif
		default:
		break;				
	}
}