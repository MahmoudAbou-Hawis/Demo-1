/************************************************************************************************************
 *************************            File Name: GPIO.c                          ************************
 *************************            Layer	   : MCAL                            ************************
 *************************            Module   : GPIO                            ************************
 *************************            Version  : V 0.0                           ************************
 *************************            Created  : 18/2/2023                       ************************
 *************************            Author   : Fatma Ezzat                     ************************
 ****Brief: This Source file defines the implementations of functions for GPIO driver**.
 ************************************************************************************************************/
/*************************** 1- Includes  **********************************/
#include "GPIO.h"

/*************************** 2- Defines   **********************************/
#define GPIO_A    ((volatile GPIO_REG *const)0x40020000)
#define GPIO_B    ((volatile GPIO_REG *const)0x40020400)
#define GPIO_C	  ((volatile GPIO_REG *const)0x40020800)
#define GPIO_D	  ((volatile GPIO_REG *const)0x40020C00)
#define GPIO_E	  ((volatile GPIO_REG *const)0x40021000)
#define GPIO_H    ((volatile GPIO_REG *const)0x40021C00)

#define NUM_OF_PORTS   6

#define BITS_OF_PIN   2

/*Mask Bits*/
#define MASK_MODER     0b11
#define MASK_OTYPER    0b1
#define MASK_PUPDR     0b11
#define MASK_OSPEEDER  0b11
#define MASK_AF		   0b1111

#define GET_MODER_BITS     0b11000
#define GET_OTYPER_BITS    0b00100
#define GET_PUPDR_BITS     0b00011

#define SET_BIT     1
#define RESET_BIT   1

#define RESET_SHIFT 16


/*************************** 3- Types     **********************************/
typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIO_REG;
/*************************** 4- Variables **********************************/
volatile GPIO_REG *const arrOfPorts[NUM_OF_PORTS]={GPIO_A,GPIO_B,GPIO_C,GPIO_D,GPIO_E,GPIO_H};

/*************************** 5- Implementation  ****************************/
/*
 * @brief:Function to initialize  a GPIO pin
 * @parameter: Struct of Data of Pin
 * @return:Error State
 * */
/*************************** 5- Implementation  ****************************/
/*
 * @brief:Function to initialize  a GPIO pin
 * @parameter: Struct of Data of Pin
 * @return:Error State
 * */
GPIO_ErrorState GPIO_InitPin(GPIO_PIN_CONFG *DataOfPin){

	GPIO_ErrorState Loc_ReturnError = GPIO_enumNOK;

	/*----------------Check on Port Number----------------*/
	if((DataOfPin->port > PORT_H)||(DataOfPin->port < PORT_A)){
		Loc_ReturnError = GPIO_enumWrongPort;

	/*----------------Check on Pin Number-----------------*/
	}else if((DataOfPin->pin > PIN_15)||(DataOfPin->pin < PIN_0)){
		Loc_ReturnError = GPIO_enumWrongPin;

	/*----------------Check on Speed of pin---------------*/
	}else if((DataOfPin->speed !=SPEED_LOW) &&(DataOfPin->speed !=SPEED_MEDIUM)&&
			 (DataOfPin->speed !=SPEED_HIGH)&&(DataOfPin->speed !=SPEED_VERY_HIGH)){
		Loc_ReturnError = GPIO_enumWrongSpeed;
	}else{
		/*Implementation*/
		Loc_ReturnError = GPIO_enumOK;


		u32 Loc_u32MODERTemp  =arrOfPorts[DataOfPin->port]->MODER;
		u32 Loc_u32OTYPERTemp =arrOfPorts[DataOfPin->port]->OTYPER;
		u32 Loc_u32PUPDR      =arrOfPorts[DataOfPin->port]->PUPDR;
		u32 Loc_u32OSPEEDR    =arrOfPorts[DataOfPin->port]->OSPEEDR;

		/*Configure MODER Register*/
		Loc_u32MODERTemp &= ~(MASK_MODER<<(BITS_OF_PIN*DataOfPin->pin));  //Every pin has 2 bits for mode configurations
		Loc_u32MODERTemp |= ((DataOfPin->mode & GET_MODER_BITS)>>3)<<(BITS_OF_PIN*DataOfPin->pin);
		arrOfPorts[DataOfPin->port]->MODER = Loc_u32MODERTemp;

		/*Configure OTYPER Register*/
		Loc_u32OTYPERTemp &= ~(MASK_OTYPER<<DataOfPin->pin);
		Loc_u32OTYPERTemp |= (((DataOfPin->mode & GET_OTYPER_BITS)>>2)<<DataOfPin->pin);
		arrOfPorts[DataOfPin->port]->OTYPER=Loc_u32OTYPERTemp;

		/*Configure PUPDR Register*/
		Loc_u32PUPDR &= ~((MASK_PUPDR)<<(BITS_OF_PIN*DataOfPin->pin));
		Loc_u32PUPDR |= (DataOfPin->mode &GET_PUPDR_BITS)<<(BITS_OF_PIN*DataOfPin->pin);
		arrOfPorts[DataOfPin->port]->PUPDR = Loc_u32PUPDR;

		/*Configure OSPEEDER Register*/
		Loc_u32OSPEEDR &=~(MASK_OSPEEDER<<(BITS_OF_PIN*DataOfPin->pin));
		Loc_u32OSPEEDR |=(DataOfPin->speed)<<(BITS_OF_PIN*DataOfPin->pin);
		arrOfPorts[DataOfPin->port]->OSPEEDR =Loc_u32OSPEEDR;
	}

	return Loc_ReturnError;
}

GPIO_ErrorState GPIO_SetPinValue(u8 port,u8 pin,u8 value){
	GPIO_ErrorState Loc_ReturnError = GPIO_enumNOK;

	/*----------------Check on Port Number----------------*/
	if((port > PORT_H)||(port < PORT_A)){
		Loc_ReturnError = GPIO_enumWrongPort;

	/*----------------Check on Pin Number----------------*/
	}else if((pin > PIN_15)||(pin < PIN_0)){
		Loc_ReturnError = GPIO_enumWrongPin;

	/*----------------Check on value----------------*/
	}else if((value!= LogicLow)&&(value!= LogicHigh)){
		Loc_ReturnError =GPIO_enumWrongValue;

	}else{

		/*Implementation*/
		Loc_ReturnError=GPIO_enumOK;

		switch(value){
			case LogicLow:
				arrOfPorts[port]->BSRR |=(RESET_BIT)<<(pin+RESET_SHIFT);

				break;
			case LogicHigh:
				arrOfPorts[port]->BSRR |=(SET_BIT<<pin);
				break;
			default:
				/*do nothing*/
				break;
			}
	}

	return Loc_ReturnError;
}

GPIO_ErrorState GPIO_GetPinValue(u8 port,u8 pin,u8 *ptr){

	GPIO_ErrorState Loc_ReturnError = GPIO_enumNOK;
	/*----------------Check on Port Number----------------*/
		if((port > PORT_H)||(port < PORT_A)){
			Loc_ReturnError = GPIO_enumWrongPort;

	/*----------------Check on Pin Number----------------*/
		}else if((pin > PIN_15)||(pin < PIN_0)){
			Loc_ReturnError = GPIO_enumWrongPin;

	/*----------------Check on Pointer Value----------------*/
		}else if(ptr==NULL){
			Loc_ReturnError = GPIO_enumNullPointer;
		}else{
			/*Implementation*/
			Loc_ReturnError =GPIO_enumOK;
			*ptr =(arrOfPorts[port]->IDR >>pin) & 1;
		}
	return Loc_ReturnError;
}

/*
 * @brief:Function to configure Alternative Function
 * @parameter: The pin number within a specific port and pointer to carry the return value
 * @return:Error State
 * */

GPIO_ErrorState GPIO_CFG_AlternativeFunction(u8 port,u8 pin,u8 Copy_AFNumber) {
	GPIO_ErrorState Loc_ReturnError = GPIO_enumNOK;
	u32 Loc_AFRValue = 0;
	/*----------------Check on Port Number----------------*/
		if((port > PORT_H)||(port < PORT_A)){
			Loc_ReturnError = GPIO_enumWrongPort;

	/*----------------Check on Pin Number----------------*/
		}else if((pin > PIN_15)||(pin < PIN_0)){
			Loc_ReturnError = GPIO_enumWrongPin;

	/*------------Check on Alternative Function Number----------*/
		}else if((Copy_AFNumber > GPIO_AF15)||(Copy_AFNumber < GPIO_AF00)){

			Loc_ReturnError = GPIO_enumWrongAF;

		}else {

	/*Implementation*/
		Loc_ReturnError =GPIO_enumOK;
		if(pin <= PIN_7){
			
			Loc_AFRValue = arrOfPorts[port]->AFRL;
			Loc_AFRValue &=~(MASK_AF <<(pin*4));
			Loc_AFRValue |= (Copy_AFNumber <<(pin*4));
			arrOfPorts[port]->AFRL = Loc_AFRValue;
		}else{
			Loc_AFRValue = arrOfPorts[port]->AFRH;
			Loc_AFRValue &=~(MASK_AF <<((pin-8)*4));
			Loc_AFRValue |= (Copy_AFNumber <<((pin-8)*4));
			arrOfPorts[port]->AFRH = Loc_AFRValue;
		}
	  }
	return Loc_ReturnError;
}