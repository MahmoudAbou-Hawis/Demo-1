/************************************************************************************************************
 *************************            File Name: GPIO.h                            ************************
 *************************            Layer	   : MCAL                              ************************
 *************************            Module   : GPIO                              ************************
 *************************            Version  : V 0.0                             ************************
 *************************            Created  : 18/2/2023                         ************************
 *************************            Author   : Fatma Ezzat                       ************************
 *************************Brief: This Header file defines functions for GPIO driver************************.
 ************************************************************************************************************/
#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

#include "STD_TYPES.h"
/********************************** 1- Defines **************************************/
/*1- General Purpose Pins*/
/*Output Pins*/
#define GPIO_GP_OUTPUT_PUSHPULL_PULL_UP			0b01001
#define GPIO_GP_OUTPUT_PUSHPULL_PULL_DOWN		0b01010

#define GPIO_GP_OUTPUT_OPENDRAIN__PULL_UP		0b01101
#define GPIO_GP_OUTPUT_OPENDRAIN__PULL_DOWN		0b01110

/*Input Pins*/
#define GPIO_GP_INPUT_PULL_UP					0b00001
#define GPIO_GP_INPUT_PULL_DOWN					0b00010
#define GPIO_GP_INPUT_FLOATING					0b00000

/*2- Alternative Functions Pins*/
/*Output Pins*/
#define GPIO_AF_OUTPUT_PUSHPULL_PULL_UP			0b10001
#define GPIO_AF_OUTPUT_PUSHPULL_PULL_DOWN		0b10010

#define GPIO_AF_OUTPUT_OPENDRAIN__PULL_UP		0b10101
#define GPIO_AF_OUTPUT_OPENDRAIN__PULL_DOWN		0b10110

/*3- Analog Pins*/
#define GPIO_ANALOG								0b11000

/*PORT Options*/
#define PORT_A     0
#define PORT_B     1
#define PORT_C     2
#define PORT_D     3
#define PORT_E     4
#define PORT_H     5


/*PIN Options*/
#define   PIN_0    0
#define   PIN_1	   1
#define   PIN_2	   2
#define   PIN_3	   3
#define   PIN_4    4
#define   PIN_5    5
#define   PIN_6    6
#define   PIN_7    7
#define   PIN_8    8
#define   PIN_9    9
#define   PIN_10   10
#define   PIN_11   11
#define   PIN_12   12
#define   PIN_13   13
#define   PIN_14   14
#define   PIN_15   15

/*Speed Options*/
#define SPEED_LOW         0b00
#define SPEED_MEDIUM	  0b01
#define SPEED_HIGH		  0b10
#define SPEED_VERY_HIGH	  0b11

#define LOGIC_LOW        0
#define LOGIC_HIGH       1

/*--------------------------- Alternative Functions --------------------------------*/
#define GPIO_AF00         (0UL)
#define GPIO_AF01         (1UL)
#define GPIO_AF02         (2UL)
#define GPIO_AF03         (3UL)
#define GPIO_AF04         (4UL)
#define GPIO_AF05         (5UL)
#define GPIO_AF06         (6UL)
#define GPIO_AF07         (7UL)
#define GPIO_AF08         (8UL)
#define GPIO_AF09         (9UL)
#define GPIO_AF10         (10UL)
#define GPIO_AF11         (11UL)
#define GPIO_AF12         (12UL)
#define GPIO_AF13         (13UL)
#define GPIO_AF14         (14UL)
#define GPIO_AF15         (15UL)


/********************************** 2- Types ****************************************/
typedef struct{

	u8 port;
	u8 pin;
	u8 speed;
	u8 mode;

}GPIO_PIN_CONFG;

typedef enum {
	GPIO_enumOK,
	GPIO_enumNOK,
	GPIO_enumNullPointer,
	GPIO_enumWrongPort,
	GPIO_enumWrongPin,
	GPIO_enumWrongAF,
	GPIO_enumWrongValue,
	GPIO_enumWrongSpeed
}GPIO_ErrorState;

/****************************** 3- Function Prototypes ******************************/
/*
 * @brief:Function to initialize  a GPIO pin
 * @parameter: Struct of Data of Pin
 * @return:Error State
 * */
GPIO_ErrorState GPIO_InitPin(GPIO_PIN_CONFG *DataOfPin);
/*
 * @brief:Function to set the value of a GPIO pin
 * @parameter: The pin number within a specific port and its value
 * @return:Error State
 * */
GPIO_ErrorState GPIO_SetPinValue(u8 port,u8 pin,u8 value);
/*
 * @brief:Function to get the value of a GPIO pin
 * @parameter: The pin number within a specific port and pointer to carry the return value
 * @return:Error State
 * */
GPIO_ErrorState GPIO_GetPinValue(u8 port,u8 pin,u8 *ptr);
/*
 * @brief:Function to configure Alternative Function
 * @parameter: The pin number within a specific port and pointer to carry the return value
 * @return:Error State
 * */

GPIO_ErrorState GPIO_CFG_AlternativeFunction(u8 port,u8 pin,u8 Copy_AFNumber) ;

#endif /* MCAL_GPIO_GPIO_H_ */
