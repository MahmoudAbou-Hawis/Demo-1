/*
*File: Sched.c
*Author:  Fatma Ezzat
*Created: 19/3/2024
*Target:  STM32F401cc
*/

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "Sched.h"

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct{
    User_RInfo runnable;
    u32 remainTime;
}Runnable_t;


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
volatile static u32 PendingCounts = 0;

extern const User_RInfo UsrRInfo[_MAX];

static Runnable_t rinfo[_MAX];
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
static void Sced_Tickcb(void){

    PendingCounts++;
}


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/
void Sched_init(void){

    /*1- Set Tick Time*/
    SYSTICK_SetTimeMS(TICK_TIME);

    /*2- Set Call back function Schedular*/
    SYSTICK_CallBack(Sced_Tickcb);
    /*3- Initialize remain time with first delay*/

    for(u32 index=0;index<_MAX;index++){
        if (UsrRInfo[index].cb)
        {
            rinfo[index].runnable= UsrRInfo[index];
            rinfo[index].remainTime = UsrRInfo[index].firstDelay;
        }
    }
}

void Sched_Start(void){

    /*Start Systick Timer*/
    SYSTICK_Start(INFINITY);

    while (1)
    {
        if(PendingCounts){
            
            PendingCounts--;

            Sched_MainFunc();
        }
    }   
}

void Sched_MainFunc(void){
    u32 index;

    for(index=0 ; index < _MAX ; index++){

        if (rinfo[index].runnable.cb &&rinfo[index].remainTime == 0)
        {
            /*Call Runnable Function*/
            UsrRInfo[index].cb();

            /*Reassign remain time with periodicity*/
            rinfo[index].remainTime = rinfo[index].runnable.periodicity;
        }
<<<<<<< HEAD
        rinfo[index].remainTime -= TICK_TIME;
=======
             rinfo[index].remainTime -= TICK_TIME;
       
        
>>>>>>> aa7d511236dd3a54b9239bbcebe6087b92e6fd69
    }
}
