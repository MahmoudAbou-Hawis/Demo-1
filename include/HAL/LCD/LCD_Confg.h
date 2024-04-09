/*
*File: 
*Author:  Fatma Ezzat
*Created:
*Target:  STM32F401cc
*/
#ifndef LCD_CONFG_H_
#define LCD_CONFG_H_

#include "Demo1_LCD.h"
/*LCD MODE*/
#define LCD_4BITS_MODE     0
#define LCD_8BITS_MODE     1

#define LCD_MODE         LCD_8BITS_MODE

#define NUM_PINS        10

/*Periodicity of LCD Task*/
#define PERIODICIY_TIME   1

typedef struct 
{
    u8 port;
    u8 pin;
}LCD_Pins_Confg;


#endif // LCD_CONFG_H_