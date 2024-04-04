/************************************************************************************************************
 *************************            File Name: SW.h                              ************************
 *************************            Layer	   : HAL                               ************************
 *************************            Module   : SWITCH                            ************************
 *************************            Version  : V 0.0                             ************************
 *************************            Created  : 18/2/2023                         ************************
 *************************            Author   : Fatma Ezzat                       ************************
 *************************Brief: This Header file defines functions for Switch driver*******************.
 ************************************************************************************************************/
#include"HSW.h"
#include"GPIO.h"


u8 swState = 0;

extern SW_CONFG_t arrayOfSw[_SW_NUM];
/*
 * @brief: A Function to initialize a switch
 * @parameter: void
 * @return :Error State
 * */
SW_ErrorState SW_init(void){

	SW_ErrorState returnError = SW_enumNOK;


	GPIO_PIN_CONFG sw;
	sw.speed = SPEED_MEDIUM;

	for(u8 sw_index=0; sw_index<_SW_NUM; sw_index++){

		sw.port = arrayOfSw[sw_index].port;
		sw.pin  = arrayOfSw[sw_index].pin;
		sw.mode = arrayOfSw[sw_index].connection;
		GPIO_InitPin(&sw);
	}
	return returnError;
}

void HSW_Runnable(void){
	u8 current;

	static u8 previous =0;
	static u8 counts;   /*Number of counts to make sure that reading value is stable*/

	GPIO_GetPinValue(arrayOfSw[Switch_1].port,arrayOfSw[Switch_1].pin,&current);
	if (current == previous)
	{
		counts++;
	}else{
		counts =0;
	}

	/*Check if there are 5 identical readings*/

	if (counts %5 == 0){
		swState =current;
	}
	
	/*Update Previous value*/
	previous =current;
}

SW_ErrorState SW_getSwState(SWs_t switchName,u8* switchState){
	SW_ErrorState returnError = SW_enumNOK;
	*switchState = swState;
	return returnError;
}