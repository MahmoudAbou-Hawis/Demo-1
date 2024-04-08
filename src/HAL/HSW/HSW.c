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


u8 swState[_SW_NUM] = {0};

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
	u8 current = 0;

	static u8 previous[_SW_NUM] = {0};
	static u8 counts[_SW_NUM] = {0};   /*Number of counts to make sure that reading value is stable*/

	for(u8 sw_index=0; sw_index<_SW_NUM; sw_index++){	

		/*Get the switch value*/
		GPIO_GetPinValue(arrayOfSw[sw_index].port,arrayOfSw[sw_index].pin,&current);

		if (current == previous[sw_index])
		{
			counts[sw_index]++;
		}else{
			counts[sw_index] =0;
		}
		/*Check if there are 5 identical readings*/

		if (counts[sw_index] %5 == 0){
			swState[sw_index] =current;
		}
	
		/*Update Previous value*/
		previous[sw_index] =current;
		
	}
}

SW_ErrorState SWITCH_enuGetStatus(SWs_t switchName,u32* switchState){
	SW_ErrorState returnError = SW_enumNOK;
	*switchState = swState[switchName];
	return returnError;
}

