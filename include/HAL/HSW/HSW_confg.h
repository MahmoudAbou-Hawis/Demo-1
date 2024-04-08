/************************************************************************************************************
 *************************            File Name: SW_confg.h                              ************************
 *************************            Layer	   : HAL                               ************************
 *************************            Module   : SWITCH                            ************************
 *************************            Version  : V 0.0                             ************************
 *************************            Created  : 18/2/2023                         ************************
 *************************            Author   : Fatma Ezzat                       ************************
 *************************Brief: This Header file defines functions for Switch driver*******************.
 ************************************************************************************************************/
#ifndef HAL_1_SW_SW_CONFG_H_
#define HAL_1_SW_SW_CONFG_H_

/*Switch Names*/

typedef enum {
	UP_SWITCH,
    DOWN_SWITCH,
    RIGHT_SWITCH,
    LEFT_SWITCH,

	/*Number of switches*/
	_SW_NUM
}SWs_t;

/*Switch Connections*/
#define SW_PULLUP      0x0001     /*GPIO_GP_INPUT_PULL_UP value*/
#define SW_PULLDOWN    0x0002	  /*GPIO_GP_INPUT_PULL_DOWN value*/


#endif /* HAL_1_SW_SW_CONFG_H_ */