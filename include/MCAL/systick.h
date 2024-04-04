/*
* File:    SYSTICK.h
* Author:  Fatma Ezzat
* Created: 18/3/2024
* Brief:   SYSTICK Driver
* Target:  STM32F401cc
*/

#ifndef MCAL_SYSTICK_SYSTICK_H_
#define MCAL_SYSTICK_SYSTICK_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "STD_TYPES.h"
#include "SYSTICK_Confg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
 typedef enum{

    /*@brief:Everything Ok, Function had Performed Correctly.*/
        SYSTICK_enumOK,
        
     /*@brief:Everything Not Ok, Function had Performed Incorrectly.*/
        SYSTICK_enumNOK,

      /*@brief:Send Null Pointer.*/
        SYSTICK_enumNullPointer,

 }SYSTICK_ErrorState;

/*@brief : Pointer to fuction*/
typedef void (*SYSTICK_CALLBACK)(void); 

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
/*
*@brief : Function to start Systick Timer
*@parameter: Timer Periodicity
*@return: Error State
*/
SYSTICK_ErrorState SYSTICK_Start(u8 Periodicity);
/*
*@brief : Function to stop Systick Timer
*@parameter:void
*@return: void
*/
void SYSTICK_Stop(void);
/*
*@brief : Function to Set Time in timer 
*@parameter: Required time
*@return: Error State
*/
SYSTICK_ErrorState SYSTICK_SetTimeMS(u32 time);
/*
*@brief : Function to take the function from application layer
*@parameter: pointer to funtion 
*@return: Error State
*/
SYSTICK_ErrorState SYSTICK_CallBack(SYSTICK_CALLBACK cbf);

void SysTick_Handler(void);

#endif // MCAL_SYSTICK_SYSTICK_H_