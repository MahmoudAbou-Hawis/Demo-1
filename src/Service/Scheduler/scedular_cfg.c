/*
*File: Sched_Confg.c
*Author:  Fatma Ezzat
*Created: 19/3/2024
*Target:  STM32F401cc
*/
#include "Sched.h"

extern void HSW_Runnable(void);
extern void APP_Runnable(void);

const User_RInfo UsrRInfo[_MAX] = {

    [SWITCHES]={
        .name ="switch bouncing",
        .periodicity =5,
        .firstDelay =0,
        .cb = HSW_Runnable
    },
    [Main_APP]={
        .name ="APP_TASK",
        .periodicity =100,
        .firstDelay =100,
        .cb = APP_Runnable
    }
};