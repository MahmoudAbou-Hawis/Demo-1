/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "NVIC.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define BASE_ADDRESS 0xE000E100
#define NUM_OF_INTERRUPTS  84

#define REG_SIZE 32
#define PARITY_REG_SIZE   8
#define IMPLEMENTED_PART  4


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
/*NVIC Registers*/
typedef struct{
    u32 ISER[8];
	u32 Reserved0[24];
	u32 ICER[8];
	u32 Reserved1[24];
	u32 ISPR[8];
	u32 Reserved2[24];
	u32 ICPR[8];
	u32 Reserved3[24];
	u32 IABR[8];
	u32 Reserved4[56];
	u32 IPR[60];
	u32 Reserved5[644];
	u32 STIR;
}NVIC_REG;


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
static volatile NVIC_REG *const NVIC = (NVIC_REG *const)BASE_ADDRESS;

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/
NVIC_ERROR_t NVIC_EnableInterrupt(u32 intNum){
    NVIC_ERROR_t ReturnError = NVIC_enumNOK;

    /*Check on The Number of interrupt*/
    if(intNum>NUM_OF_INTERRUPTS){
      ReturnError=NVIC_enumWrongIntNum;  
    }else{
        ReturnError =NVIC_enumOK;
        /*Implementation*/
        u8 actualNum = intNum % REG_SIZE;
        NVIC->ISER[intNum/REG_SIZE] |=(1<<actualNum);
    }
   return ReturnError;
}
NVIC_ERROR_t NVIC_DisableInterrupt(u32 intNum){
    NVIC_ERROR_t ReturnError = NVIC_enumNOK;

    /*Check on The Number of interrupt*/
    if(intNum>NUM_OF_INTERRUPTS){
      ReturnError=NVIC_enumWrongIntNum;  
    }else{
      ReturnError =NVIC_enumOK;
      /*Implementation*/
    u8 actualNum = intNum % REG_SIZE;
    NVIC->ICER[intNum/REG_SIZE] |=(1<<actualNum);
    }
     return ReturnError;
}

NVIC_ERROR_t NVIC_SetPending(u32 intNum){
    NVIC_ERROR_t ReturnError = NVIC_enumNOK;

    /*Check on The Number of interrupt*/
    if(intNum>NUM_OF_INTERRUPTS){
      ReturnError=NVIC_enumWrongIntNum;  
    }else{
      ReturnError =NVIC_enumOK;
      /*Implementation*/
    u8 actualNum = intNum % REG_SIZE;
    NVIC->ISPR[intNum/REG_SIZE] |=(1<<actualNum);
    }
    return ReturnError;
}
NVIC_ERROR_t NVIC_ClearPending(u32 intNum){
    NVIC_ERROR_t ReturnError = NVIC_enumNOK;

    /*Check on The Number of interrupt*/
    if(intNum>NUM_OF_INTERRUPTS){
      ReturnError=NVIC_enumWrongIntNum;  
    }else{
      ReturnError =NVIC_enumOK;
      /*Implementation*/
    u8 actualNum = intNum % REG_SIZE;
    NVIC->ICPR[intNum/REG_SIZE] |=(1<<actualNum);
    }
    return ReturnError; 
}
NVIC_ERROR_t NVIC_GetActiveStatus(u32 intNum,u8* Add_ActiveState){
    NVIC_ERROR_t ReturnError = NVIC_enumNOK;

    /*Check on The Number of interrupt*/
    if(intNum>NUM_OF_INTERRUPTS){
      ReturnError=NVIC_enumWrongIntNum; 
    }
    /*Check on The value of the pointer*/
    else if(Add_ActiveState==NULL){
        ReturnError = NVIC_enumNullPointer;
    }else{
      ReturnError =NVIC_enumOK;
      /*Implementation*/
    u8 actualNum = intNum % REG_SIZE;
    *Add_ActiveState = (NVIC->IABR[intNum/REG_SIZE]>>actualNum)&1;
    }
    return ReturnError;
}
NVIC_ERROR_t NVIC_GenerateSWInterrupt(u32 intNum){
     NVIC_ERROR_t ReturnError = NVIC_enumNOK;

    /*Check on The Number of interrupt*/
    if(intNum>NUM_OF_INTERRUPTS){
      ReturnError=NVIC_enumWrongIntNum;  
    }else{
      ReturnError =NVIC_enumOK;
      /*Implementation*/
       NVIC->STIR =  intNum;
    }
    return ReturnError;
}
NVIC_ERROR_t NVIC_SetPriority(u8 intNum,u8 priority){
    NVIC_ERROR_t ReturnError = NVIC_enumNOK;

    if(intNum>NUM_OF_INTERRUPTS){
      ReturnError=NVIC_enumWrongIntNum;  
    }
    else {
      ReturnError =NVIC_enumOK;
      /*Implementation*/
    u8 regNumber = intNum/4;
    u8 indexNumber = intNum%4;
    NVIC->IPR[regNumber] |=((priority<<IMPLEMENTED_PART)<<((PARITY_REG_SIZE)*indexNumber));
    }
    return ReturnError;
}