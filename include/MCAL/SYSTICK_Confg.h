/*
* File:    SYSTICK_Confg.h
* Author:  Fatma Ezzat
* Created: 18/3/2024
* Brief:   SYSTICK Driver
* Target:  STM32F401cc
*/

#ifndef MCAL_SYSTICK_SYSTICK_CONFG_H_
#define MCAL_SYSTICK_SYSTICK_CONFG_H_

/*Timer Periodicity*/
#define ONE_TIME  0
#define INFINITY   1

/*Select Frequency of AHB*/
#define PROCESSPR_CLK_FRQ 16000000

/*Timer Clock Source*/
#define MP_CLK_SRC          1
#define MP_CLK_SRC_DIV_8    0

#define SYSTICK_CLK_SRC  MP_CLK_SRC

#endif // MCAL_SYSTICK_SYSTICK_CONFG_H_