/*
* File:    SYSTICK.c
* Author:  Fatma Ezzat
* Created: 18/3/2024
* Brief:   SYSTICK Driver
* Target:  STM32F401cc
*/

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "SYSTICK.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/


#define BASE_ADDRESS        0xE000E010

#define ENABLE_TIMER_BIT    0
#define TICKINT_BIT         1
#define CLKSOURCE_BIT       2


/*Modes*/
#define ENABLE     1
#define DISABLE    0

/*Timer State*/
#define START      1
#define STOP       0

/*Clock Source of Timer*/
#define AHB_DIV_BY_8        0
#define PROCESSOR_CLOCk     1

#define SYSTICK_CLKSRC  PROCESSOR_CLOCk

#define MAX_RELOAD_VALUE    0x00FFFFFF
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct{
    u32 CTRL;
    u32 LOAD;
    u32 VAL;
    u32 CALIB;
}SYSTICK_REG_t;


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
 static volatile SYSTICK_REG_t *const SYSTICK  = (SYSTICK_REG_t *const) BASE_ADDRESS; 


/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
static u8 Timer_Periodicity =0;
static SYSTICK_CALLBACK HandlerFunc = NULL;

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/
/*
*@brief : Function to start Systick Timer
*@parameter: Timer Periodicity
*@return: Error State
*/
SYSTICK_ErrorState SYSTICK_Start(u8 Periodicity){

/*------------------------------------------Validation---------------------------------------------------*/
    SYSTICK_ErrorState returnError =SYSTICK_enumOK;

    if(Periodicity > INFINITY){
        returnError =SYSTICK_enumNOK;
    }else{
/*------------------------------------------Implementation------------------------------------------------*/
    /*Configure Systick Timer*/

    /*1- Select Clock Source*/
    SYSTICK->CTRL |=(SYSTICK_CLKSRC<<CLKSOURCE_BIT);
    
    /*2-Enable Interrupt*/
    SYSTICK->CTRL |=(ENABLE<<TICKINT_BIT);

    /*3-Clear Timer Register*/
    SYSTICK->VAL = 0;
    /*4-Assign periodicity*/
    Timer_Periodicity = Periodicity;

    /*5-Enable SYSTICK Timer*/
    SYSTICK->CTRL |=(START<<ENABLE_TIMER_BIT);
    }
   return returnError;
}

/*############################################################################################################*/
/*
*@brief : Function to stop Systick Timer
*@parameter:void
*@return: void
*/
void SYSTICK_Stop(void){
    SYSTICK->CTRL &=(STOP<<ENABLE_TIMER_BIT);
}

/*############################################################################################################*/
/*
*@brief : Function to Set Time in timer 
*@parameter: Required time
*@return: Error State
*/
SYSTICK_ErrorState SYSTICK_SetTimeMS(u32 time){

    u32 Loc_StkClockFrequency = ((SYSTICK_CLK_SRC == MP_CLK_SRC)? PROCESSPR_CLK_FRQ : (PROCESSPR_CLK_FRQ/8));

    /*
      1- Total Required Time = NumOfCounts/Frequency;
      2- Divide by 1000 to get time in Mili Second
      3- Subtract 1 bec It starts counting from zero 
    */
    u32 Loc_StkNumOfCounts =(u32)(((u64)Loc_StkClockFrequency *(u64) time)/(u64)1000); 

/*------------------------------------------Validation---------------------------------------------------*/
    SYSTICK_ErrorState returnError =SYSTICK_enumOK;
    if (time >MAX_RELOAD_VALUE)
    {
        returnError =SYSTICK_enumNOK;
    }else{
/*------------------------------------------Implementation-----------------------------------------------*/

    SYSTICK->LOAD =Loc_StkNumOfCounts -1;
    }
return returnError;
}

/*############################################################################################################*/
/*
*@brief : Function to take the function from application layer
*@parameter: pointer to funtion 
*@return: Error State
*/
SYSTICK_ErrorState SYSTICK_CallBack(SYSTICK_CALLBACK cbf){
/*------------------------------------------Validation---------------------------------------------------*/
    SYSTICK_ErrorState returnError =SYSTICK_enumOK;
    if(cbf==NULL){
        returnError = SYSTICK_enumNullPointer;
/*------------------------------------------Implementation-----------------------------------------------*/

    }else{
        HandlerFunc =cbf;
    }

return returnError;
}

/*############################################################################################################*/
void SysTick_Handler(void){

    if (Timer_Periodicity==ONE_TIME){

            SYSTICK_Stop();
    }
    if(HandlerFunc!=NULL){
        HandlerFunc();
    }
}