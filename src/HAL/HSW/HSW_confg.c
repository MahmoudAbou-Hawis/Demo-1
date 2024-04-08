/************************************************************************************************************
 *************************            File Name: SW_confg.c                             ************************
 *************************            Layer	   : HAL                               ************************
 *************************            Module   : SWITCH                            ************************
 *************************            Version  : V 0.0                             ************************
 *************************            Created  : 18/2/2023                         ************************
 *************************            Author   : Fatma Ezzat                       ************************
 *************************Brief: This Header file defines functions for Switch driver*******************.
 ************************************************************************************************************/
#include "HSW.h"
#include"GPIO.h"

SW_CONFG_t arrayOfSw[_SW_NUM]={

	[UP_SWITCH]={
		.port = PORT_A,
		.pin  = PIN_0,
		.connection= SW_PULLDOWN
	},
	[DOWN_SWITCH]={
		.port = PORT_A,
		.pin  = PIN_1,
		.connection= SW_PULLDOWN
	},
	[RIGHT_SWITCH]={
		.port = PORT_A,
		.pin  = PIN_2,
		.connection= SW_PULLDOWN
	},
	[LEFT_SWITCH]={
		.port = PORT_A,
		.pin  = PIN_3,
		.connection= SW_PULLDOWN
	},
		
};