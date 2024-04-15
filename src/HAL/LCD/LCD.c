/*
*File: Source file of LCD
*Author:  Fatma Ezzat
*Created: 3/25/2024
*Target:  STM32F401cc
*/
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "Demo1_LCD.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define POWER_ON_TIME              30
#define FUNC_SET_TO_DISPLAY        20
#define DISPLAY_TO_ENTRY_MODE      20
#define ENTRY_MODE_TO_END          10

#define MAX_NUM_OF_CHARACTERS      16

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
static u8 LCD_State = OFF_State;
u16 counter=0;
static UserReq User_req ={.state =Ready};
static u8 enable_State = Enable_Low;
extern LCD_Pins_Confg ArrayOfPins[NUM_PINS];


/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
static void initStateMachine(void);
static void LCD_WriteData(u8 Data);
static u8   GET_BIT(u8 Register,u8 BitNum);
static void LCD_InitPins(void);
static void LCD_write_Proc(void);
static void LCD_clearScreen_Proc(void);
static void LCD_setPosition_Proc(void);


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

/************************************************************************/
/*					        USER APIS             		                */
/* @brief:
Take information from user about his request and assign them in Globa struct
*/
/************************************************************************/

/*
*@brief : Function to configure LCD pins as outputs
*@parameter: Pointer to function 
*@return: void
*/
void LCD_InitPins(void){
     GPIO_PIN_CONFG LCD_Pin;
     

 	/*Speed & Mode of pins are common between all pins*/
	LCD_Pin.speed = SPEED_MEDIUM;
	LCD_Pin.mode  = GPIO_GP_OUTPUT_PUSHPULL_PULL_UP;

    /*For every pin*/
    for(u8 indx =0;indx<NUM_PINS;indx++){
            LCD_Pin.port = ArrayOfPins[indx].port;
            LCD_Pin.pin  = ArrayOfPins[indx].pin;
            GPIO_InitPin(&LCD_Pin);    
    }
}
/*
*@brief : Function to initialize LCD
*@parameter: Pointer to function 
*@return: Error state
*/

LCD_enuErrorStatus LCD_initAsync(ReqCallBack_t CB){
    /********************************* Validation *******************************/
    LCD_enuErrorStatus Ret_enumErrorStatus = LCD_enumNOk;
    if(!CB){
        Ret_enumErrorStatus = LCD_enumNullPointer;
    }else{
        Ret_enumErrorStatus = LCD_enumOk;
    /********************************* Implementation *******************************/
        if (User_req.state == Ready){
            LCD_State = Init_State;
            User_req.state = Busy;
            User_req.cb =CB;
        }
    }
    return Ret_enumErrorStatus;
}

/*
*@brief  : Function to clear LCD screen
*@param  : Pointer to function
*@return : Error state
*/
LCD_enuErrorStatus LCD_clearScreenAsync(ReqCallBack_t CB){
    /********************************* Validation *******************************/
    LCD_enuErrorStatus Ret_enumErrorStatus = LCD_enumNOk;
    if(!CB){
        Ret_enumErrorStatus = LCD_enumNullPointer;
    }else{
        Ret_enumErrorStatus = LCD_enumOk;
    /********************************* Implementation *******************************/
         if ((User_req.state == Ready)&&(LCD_State ==Operational_State)){
            User_req.state = Busy;
            User_req.type = LCD_Req_ClearScreen;
            User_req.cb =CB;
        }
    }
    return Ret_enumErrorStatus;
}

/*
*@brief  : Function to display a string on the LCD screen
*@param  : String, its length and Pointer to function 
*@return : Error state
*/
LCD_enuErrorStatus LCD_writeStringAsync(const u8 *s,u8 length,ReqCallBack_t CB){
    /********************************* Validation *******************************/
    LCD_enuErrorStatus Ret_enumErrorStatus = LCD_enumNOk;
    if(!CB){
        Ret_enumErrorStatus = LCD_enumNullPointer;
    }
    else if(!s){
        Ret_enumErrorStatus = LCD_enumNullPointer;
    }
    else if(length > MAX_NUM_OF_CHARACTERS){
        Ret_enumErrorStatus =LCD_enumWrongStringLength;
    }else{
        Ret_enumErrorStatus = LCD_enumOk;
    /********************************* Implementation *******************************/
         if ((User_req.state == Ready)&&(LCD_State ==Operational_State)){
            User_req.string = s;
            User_req.stringLength =length;
            User_req.state = Busy;
            User_req.type = LCD_Req_write;  
           User_req.cb =CB;
        }
    }
    return Ret_enumErrorStatus;
}
/*
*@brief  : Function to jump on a specific location on DDRAM (On the LCD screen)
*@param  : The position of the desired location on the LCD (X:Row & Y:Columns) 
*@return : Error state
*/
LCD_enuErrorStatus LCD_setCursorPosAsync(u8 PosX, u8 PosY,ReqCallBack_t CB){
    /********************************* Validation *******************************/
    LCD_enuErrorStatus Ret_enumErrorStatus = LCD_enumNOk;
    if ((PosX > SECOND_LINE)||(PosY > MAX_NUM_OF_CHARACTERS))
    {
        Ret_enumErrorStatus =LCD_enumWrongPosition;
    }else if(!CB){
        Ret_enumErrorStatus = LCD_enumNullPointer;

    }else{
        Ret_enumErrorStatus = LCD_enumOk;
    /********************************* Implementation *******************************/
        if ((User_req.state == Ready)&&(LCD_State ==Operational_State)){
            User_req.posx =PosX;
            User_req.posy =PosY;
            User_req.state = Busy;
            User_req.type = LCD_Req_SetPos; 
            User_req.cb =CB;
        }
    }
    return Ret_enumErrorStatus;
}
/*
*@brief : Function to get the status of the LCD
*@parameter: Pointer to function 
*@return: void
*/
LCD_enuErrorStatus  LCD_getState(u8 * Addu8_value){
    /********************************* Validation *******************************/
    LCD_enuErrorStatus Ret_enumErrorStatus = LCD_enumNOk;
    if(!Addu8_value){
        Ret_enumErrorStatus = LCD_enumNullPointer;
    }else{
        Ret_enumErrorStatus = LCD_enumOk;
    /********************************* Implementation *******************************/
     *Addu8_value = User_req.state;
    }
    return Ret_enumErrorStatus;
}
/*#######################################################################################################################################*/
/************************************************************************/
/*					         LCD Task              		                */
/************************************************************************/
void LCD_Task_Runnable(void){

  counter += PERIODICIY_TIME;

    if (LCD_State == Init_State){
        initStateMachine();
    }
    else if(LCD_State == Operational_State){   /*LCD is converted to operational state in the ultimate stage og*/
        
        if(User_req.state == Busy){
            switch(User_req.type){
                case LCD_Req_write:
                LCD_write_Proc();
                break;
                case LCD_Req_ClearScreen:
                LCD_clearScreen_Proc();
                break;
                case LCD_Req_SetPos:
                LCD_setPosition_Proc();
                break;
            }
        }
    }
}
/*#######################################################################################################################################*/
/************************************************************************/
/*					    LCD Helper Functions             	            */
/************************************************************************/

static void initStateMachine(void){
    static u8 initState = Power_On ;
  
    switch (initState)
    {
    case Power_On:
   
    if (counter>POWER_ON_TIME)
    {
        /*Action*/
        /*Clear Counter*/
        LCD_InitPins();
        initState = Function_Set;
        counter =0;
    }
        break;
    case Function_Set:
        /*Action*/
        LCD_sendCommand(LCD_FUNCTION_SET_8BIT_2LINES_5x7);
        //LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON);
        if((enable_State == Enable_Low)&&(counter>FUNC_SET_TO_DISPLAY)){
            /*Transition*/
            initState = Dispay_setting;
            counter =0;
        }
        break;

    case Dispay_setting:
        /*Action*/
        LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
        if((enable_State == Enable_Low)&&(counter>DISPLAY_TO_ENTRY_MODE)){
            /*Transition*/
             initState = Dispay_clear;
              counter =0;
        }
        break;
    case Dispay_clear:
        /*Action*/
        LCD_sendCommand(LCD_CLEAR);
        if((enable_State == Enable_Low)&&(counter>DISPLAY_TO_ENTRY_MODE)){
            /*Transition*/
             initState = Entry_Mode;
              counter =0;
        }
        break;
    case Entry_Mode:
        /*Action*/
        LCD_sendCommand(LCD_ENTRY_MODE_SET_INC_SHIFT_OFF);
       if((enable_State == Enable_Low)&&(counter>ENTRY_MODE_TO_END)){
            /*Transition*/
             initState = End_init;
             counter =0;
        }
        break;

    case End_init:
    /*Action*/
    LCD_State = Operational_State; /*It finishes the initialization level*/
    User_req.cb();

    /*Transition*/
        break;
    default:
        /*Do nothing*/
        break;
    }
}

 static void LCD_write_Proc(void){
    User_req.state = Busy;
    User_req.type  = LCD_Req_write;
    static u8 index = 0;

    if (index < User_req.stringLength){
        LCD_WriteData(User_req.string[index]);
        if(enable_State == Enable_Low){
          
            index ++;
        }
       
    }else{
        index =0; 
        User_req.state = Ready;
       User_req.cb();
    }
 }
 static void LCD_clearScreen_Proc(void){

    LCD_sendCommand(LCD_CLEAR);
      if(enable_State == Enable_Low){
         User_req.state = Ready;
          User_req.cb();
      }
 }
 
static void LCD_setPosition_Proc(void){
    u8 address=0;
	
    switch (User_req.posx)
    {
    case FIRST_LINE:
		address = User_req.posy-1;
		break;
	case SECOND_LINE:
		address = LCD_SECOND_LINE_START + User_req.posy-1;
		 break;
    default:
        /*do nothing*/
        break;
    }
    LCD_sendCommand(LCD_DDRAM_ADDRESS + address);

    if(enable_State == Enable_Low){
        User_req.state = Ready;
         User_req.cb();
     }

}
/*
*@brief  : Function to execute the given instruction 
*@param  : ASCII code that represents the command or instruction that needs to be executed
*@return : void
*/
 void LCD_sendCommand(u8 Command){

    /*Set Register Select Pin*/
    GPIO_SetPinValue(ArrayOfPins[RS].port,ArrayOfPins[RS].pin,LOGIC_LOW);

    switch (enable_State)
    {
    case Enable_Low:

        for(u8 index=0;index<NUM_PINS;index++){
            GPIO_SetPinValue(ArrayOfPins[index].port,ArrayOfPins[index].pin,GET_BIT(Command,index));
        }
        enable_State = Enable_High;
        /*Set Enable Pin*/
        GPIO_SetPinValue(ArrayOfPins[EN].port,ArrayOfPins[EN].pin,LOGIC_HIGH);
        break;

    case Enable_High:
        /*Clear Enable Pin*/
        GPIO_SetPinValue(ArrayOfPins[EN].port,ArrayOfPins[EN].pin,LOGIC_LOW);
        enable_State = Enable_Low;
        break;
    default:
        break;
    }
}
/*
*@brief  : Function to display the character on the LCD
*@param  : ASCII code that represents the desired data to display on the LCD
*@return : void
*/
static void LCD_WriteData(u8 Data){

    /*Set Register Select Pin*/
    GPIO_SetPinValue(ArrayOfPins[RS].port,ArrayOfPins[RS].pin,LOGIC_HIGH);

    switch (enable_State)
    {
    case Enable_Low:

        for(u8 index=0;index<NUM_PINS;index++){
            GPIO_SetPinValue(ArrayOfPins[index].port,ArrayOfPins[index].pin,GET_BIT(Data,index));
        }
        enable_State = Enable_High;
        /*Set Enable Pin*/
        GPIO_SetPinValue(ArrayOfPins[EN].port,ArrayOfPins[EN].pin,LOGIC_HIGH);
        break;
        
    case Enable_High:
        /*Clear Enable Pin*/
        GPIO_SetPinValue(ArrayOfPins[EN].port,ArrayOfPins[EN].pin,LOGIC_LOW);
        enable_State = Enable_Low;
        break;
    default:
        break;
    }
}

 static u8 GET_BIT(u8 Register,u8 BitNum){

    return ((Register>>BitNum)&1);
}