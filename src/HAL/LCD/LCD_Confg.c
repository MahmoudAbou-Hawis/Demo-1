/*
*File: 
*Author:  Fatma Ezzat
*Created:
*Target:  STM32F401cc
*/
#include "LCD_Confg.h"

LCD_Pins_Confg ArrayOfPins[]={
   
 #if LCD_MODE == LCD_8BITS_MODE
  [D0] = 
  {
	  .port = PORT_A,
	  .pin  = PIN_0,
  },
  [D1] =
  {
	  .port = PORT_A,
	  .pin  = PIN_1,
  },
  [D2] =
  {
	  .port = PORT_A,
	  .pin  = PIN_2,
  },
  [D3] =
  {
	  .port = PORT_A,
	  .pin  = PIN_3,
  },
  #endif
  
  [D4] =
  {
	  .port = PORT_A,
	  .pin  = PIN_4,
  },
  [D5] =
  {
	  .port = PORT_A,
	  .pin  = PIN_5,
	},
  [D6] =
  {
  	.port = PORT_A,
  	.pin  = PIN_6,
  },
  [D7] =
  {
  	.port = PORT_A,
  	.pin  = PIN_7,
  },
  [EN] =
  {
	  .port = PORT_A,
	  .pin  = PIN_8, 
  },
  [RS] =
  {
	  .port = PORT_A,
	  .pin  = PIN_9
  }
};