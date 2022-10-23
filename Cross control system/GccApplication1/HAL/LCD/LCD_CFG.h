/*
 * LCD.c
 *
 * Created : 19/04/2022 
 * Version : 2
 * Author  : HOSSAM MOSTAFA
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

//LCD_MODE options --> [ _4_BIT_MODE , _8_BIT_MODE ] 
#define LCD_MODE				   _4_BIT_MODE
//#define LCD_MODE				   _8_BIT_MODE



//#define KIT
#define KIT

#if defined (PROTEUS)
/* for using 8 bit mode uncomment this lines */

// #define LCD_DATA_PIN_0             GPIO_B,GPIO_PIN_0
// #define LCD_DATA_PIN_1             GPIO_B,GPIO_PIN_1
// #define LCD_DATA_PIN_2             GPIO_B,GPIO_PIN_2
// #define LCD_DATA_PIN_3             GPIO_B,GPIO_PIN_3


#define LCD_DATA_PIN_4             GPIO_A,GPIO_PIN_3
#define LCD_DATA_PIN_5             GPIO_A,GPIO_PIN_4
#define LCD_DATA_PIN_6             GPIO_A,GPIO_PIN_5
#define LCD_DATA_PIN_7             GPIO_A,GPIO_PIN_6

#define LCD_RS_PIN                 GPIO_A,GPIO_PIN_1
#define LCD_EN_PIN				   GPIO_A,GPIO_PIN_2

#define LCD_DATA_PORT			   PORTA

#elif defined(KIT)

#define LCD_DATA_PIN_4             GPIO_B,GPIO_PIN_0
#define LCD_DATA_PIN_5             GPIO_B,GPIO_PIN_1
#define LCD_DATA_PIN_6             GPIO_B,GPIO_PIN_2
#define LCD_DATA_PIN_7             GPIO_B,GPIO_PIN_4

#define LCD_RS_PIN                 GPIO_A,GPIO_PIN_3
#define LCD_EN_PIN				   GPIO_A,GPIO_PIN_2

#define LCD_DATA_PORT			   PORTB

#endif

#endif /* LCD_CFG_H_ */