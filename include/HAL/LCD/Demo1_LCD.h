/*
*File:  Header File of LCD
*Author:  Fatma Ezzat
*Created: 3/25/2024
*Target:  STM32F401cc
*/

#ifndef LCD_H_
#define LCD_H_
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "GPIO.h"
#include "STD_TYPES.h"
#include "LCD_Confg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
/************************************************************************/
/*					           LCD COMMANDS		                        */
/************************************************************************/
#define LCD_CLEAR								                0x01
#define LCD_RETURN_HOME							                0x02
#define LCD_ENTRY_MODE_SET_DEC_SHIFT_OFF		                0x04
#define LCD_ENTRY_MODE_SET_INC_SHIFT_OFF		                0x06
#define LCD_ENTRY_MODE_SET_DEC_SHIFT_ON			                0x05
#define LCD_ENTRY_MODE_SET_DEC_SHIFT_ON			                0x05
#define LCD_ENTRY_MODE_SET_INC_SHIFT_ON			                0x07
#define LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF	                0x08
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF		                0x0C
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF		                0x0E
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON		                0x0F
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON		                0x0D
#define LCD_SHIFT_CURSOR_LEFT					                0x10
#define LCD_SHIFT_CURSOR_RIGHT					                0x14
#define LCD_SHIFT_DISPLAY_LEFT					                0x18
#define LCD_SHIFT_DISPLAY_RIGHT					                0x1C
#define LCD_FUNCTION_SET_8BIT_2LINES_5x7						0x38	
#define LCD_FUNCTION_SET_4BIT_2LINES_5x8						0x28	
#define LCD_CGRAM_ADDRESS						                0x40						
#define LCD_DDRAM_ADDRESS						                0x80	
#define LCD_SECOND_LINE_START                                   0x40


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef void (*ReqCallBack_t)(void);

/*LCD Pins Configuration*/
typedef enum{
    #if LCD_MODE == LCD_8BITS_MODE
    D0,
    D1,
    D2,
    D3,
    #endif
    D4,
    D5,
    D6,
    D7,
    EN,
    RS
}Data_Pins;


/*
 *@brief : The Error List Type                                           
*/
typedef enum{
	/*
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	LCD_enumOk,
	/*
	 *@brief : Everything NOT Ok, Function had Performed InCorrectly.
	 */
	LCD_enumNOk,             
	/*
	 *@brief : Select Wrong pin Configuration
	 */    
	LCD_enumWrongcConfiguration,      
	/*
	 *@brief : Select Position Not exist ! .
	 */
	LCD_enumWrongPosition,
	/*
	 *@brief : Send Null Pointer
     */
    LCD_enumNullPointer, 
    /*
	 *@brief : Send string length that exceeds 16 characters
     */
    LCD_enumWrongStringLength
}LCD_enuErrorStatus;

/*LCD Operation Modes*/
typedef enum{

    OFF_State,
    Init_State,
    Operational_State
}LCD_States;

/*User Requests*/
typedef enum {

    LCD_Req_write,
    LCD_Req_ClearScreen,
    LCD_Req_SetPos
}LCD_Operations;


typedef enum {

    Ready,
    Busy
}RequestState;

/*Operations of initialization stage*/
typedef enum {
    Power_On,
    Function_Set,
    Entry_Mode,
    Dispay_setting,
    Dispay_clear,
    End_init
}LCD_init_Operations;


typedef struct 
{
    const u8 * string;
    u8  stringLength;
    u8  state;
    u8 type;
    u8 posx;
    u8 posy;
    ReqCallBack_t cb;
}UserReq;


typedef enum{
    Enable_Low,
    Enable_High
}Enable_State;


/*Screen of LCD*/
#define FIRST_LINE   1
#define SECOND_LINE  2

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
/*
*@brief : Function to initialize LCD
*@parameter: Pointer to function 
*@return: Error state
*/
LCD_enuErrorStatus LCD_initAsync(ReqCallBack_t CB);
/*
*@brief : Function to clear screen  of LCD
*@parameter: Pointer to function
*@return: Error state
*/
LCD_enuErrorStatus LCD_clearScreenAsync(ReqCallBack_t CB);
/*
*@brief  : Function to display a string on the LCD screen
*@param  : String, its length and Pointer to function 
*@return : Error state
*/
LCD_enuErrorStatus LCD_writeStringAsync(const u8 *s,u8 length,ReqCallBack_t CB);
/*
*@brief  : Function to jump on a specific location on DDRAM (On the LCD screen)
*@param  : The position of the desired location on the LCD (X:Row & Y:Columns) 
*@return : Error state
*/
LCD_enuErrorStatus LCD_setCursorPosAsync(u8 PosX, u8 PosY,ReqCallBack_t CB);
/*
*@brief : Function to get the status of the LCD
*@parameter: Pointer to function 
*@return: Error state
*/
LCD_enuErrorStatus  LCD_getState(u8 * Addu8_value);
 void LCD_sendCommand(u8 Command);

#endif // LCD_H_