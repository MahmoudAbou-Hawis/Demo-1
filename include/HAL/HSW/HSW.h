/************************************************************************************************************
 *************************            File Name: SW.h                              ************************
 *************************            Layer	   : HAL                               ************************
 *************************            Module   : SWITCH                            ************************
 *************************            Version  : V 0.0                             ************************
 *************************            Created  : 18/2/2023                         ************************
 *************************            Author   : Fatma Ezzat                       ************************
 *************************Brief: This Header file defines functions for Switch driver**********************
 ************************************************************************************************************/
#ifndef HAL_1_SW_SW_H_
#define HAL_1_SW_SW_H_

#include "STD_TYPES.h"
#include "HSW_confg.h"

/**
 *@brief : The Error List Type
 */
typedef enum{
	/**
	*@brief : Everything Ok, Function had Performed Correctly.
	 */
	SW_enumOK=0,
	/**
	*@brief : Everything NOT Ok, Function had Performed Incorrectly.
	*/
	SW_enumNOK,
	/**
	*@brief : Select port number not exist
	 */
	SW_enumWrongPortNumber,
	/**
	*@brief : Select pin number not exist
	 */
	SW_enumWrongPinNumber,
	/**
	*@brief : Send Null Pointer
	*/
	Sw_enumNullPointer

}SW_ErrorState;

#define PRESSED		     1
#define NOTPRESSED     	 0

/*Switch Parameters*/
typedef struct{
	u32 port;
	u32 pin;
	u32 connection;
}SW_CONFG_t;

/*
 * @brief: A Function to initialize a switch
 * @parameter: void
 * @return :Error State
 * */
SW_ErrorState SW_init(void);

/*
 * @brief: A Function to get the state of switch --> Pressed or Not Pressed
 * @parameter: The pin number of switch within a specific port
 * @return :Error State
 * */
SW_ErrorState SWITCH_enuGetStatus(SWs_t switchName,u32* switchState);



#endif /* HAL_1_SW_SW_H_ */