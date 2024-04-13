/******************************************************************************/
/**
 * @file FILE.c
 * @brief 
 *
 * @par Project Name
 * 
 *
 * @par Code Language
 * C
 *
 * @par Description
 * 
 * 
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "LCD_Control.h"
#include "CSwitch.h"
#include "Demo1_LCD.h"
#include "RCC.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/


/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/
static CLCD_info_t * infos = {0};
static CLCD_info_t LastInfo = {0};
uint8_t date[11] = {0};
uint8_t time[9]  = {0};
uint8_t stopwatch[13]={0};
/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION PROTOTYPES */
/******************************************************************************/
void showDataInNormalMode(void);
void convertNumberToString(uint8_t * ptr , uint32_t len , uint32_t number);
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/

void call()
{


}

void printDate(void)
{
    LCD_writeStringAsync(date,10,call);
}

void SetCursorDate(void)
{
    LCD_setCursorPosAsync(SECOND_LINE,1,printDate);
}

void PrintTime(void)
{
    LCD_writeStringAsync(time,8,SetCursorDate);
}
void PrintStopWatchMilli (void)
{
    LCD_writeStringAsync(stopwatch+9,3,call);
}
void PrintStopWatchSecond (void)
{
    LCD_writeStringAsync(stopwatch+6,2,call);
}
void PrintStopWatchMinute (void)
{
    LCD_writeStringAsync(stopwatch+3,2,call);
}
void PrintStopWatchHour (void)
{
    LCD_writeStringAsync(stopwatch,2,call);
}


void convertNumberToString(uint8_t * ptr , uint32_t len , uint32_t number)
{
    for(int num = len -1; num >= 0 ;num--)
    {
        ptr[num] = ((number%10)+'0');
        number /= 10;
    }
}

void showDateAndTimeInNormalMode(void)
{
    convertNumberToString(date,4,infos->year);
    convertNumberToString(date+5,2,infos->month);
    convertNumberToString(date+8,2,infos->day);
    convertNumberToString(time,2,infos->hour);
    convertNumberToString(time+3,2,infos->minute);
    convertNumberToString(time+6,2,infos->second);
    if(LastInfo.second != infos->second)
        LCD_setCursorPosAsync(FIRST_LINE,2,PrintTime);
}
void showTimeinStopWatchMode(void)
{
    
    convertNumberToString(stopwatch,2,infos->StopWatchHour);
    convertNumberToString(stopwatch+3,2,infos->StopWatchMinute);
    convertNumberToString(stopwatch+6,2,infos->StopWatchSeconds);
    convertNumberToString(stopwatch+9,3,infos->StopWatchMilli);
    if(LastInfo.StopWatchHour != infos->StopWatchHour)
        LCD_setCursorPosAsync(FIRST_LINE,1,PrintStopWatchHour);
    else if (LastInfo.StopWatchMinute != infos->StopWatchMinute)
        LCD_setCursorPosAsync(FIRST_LINE,4,PrintStopWatchMinute);  
    else if(LastInfo.StopWatchSeconds != infos->StopWatchSeconds)
        LCD_setCursorPosAsync(FIRST_LINE,7,PrintStopWatchSecond);
    else if (LastInfo.StopWatchMilli != infos->StopWatchMilli)
        LCD_setCursorPosAsync(FIRST_LINE,10,PrintStopWatchMilli);
    
    
         
}



/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/
void CLCD_Init(void)
{
    RCC_enuEnablePeripheral(PERIPHERAL_GPIOB);
    date[4] = '/';
    date[7] = '/';
    time[2] = ':';
    time[5] = ':';
    stopwatch[2]=':';
    stopwatch[5]=':';
    stopwatch[8]=':';

    LCD_initAsync(call);
}
void CLCD_Write(CLCD_info_t * info)
{
    infos = info;
    switch (info->state)
    {
    case NORMAL:
        showDateAndTimeInNormalMode();
        LastInfo.day = info->day;
        LastInfo.month = info->month;
        LastInfo.year = info->year;
        LastInfo.second = info->second;
        LastInfo.minute = info->minute;
        LastInfo.hour = info->hour;
        break;
    case STOPWATCH:
        showTimeinStopWatchMode();
        LastInfo.StopWatchHour=info->StopWatchHour;
        LastInfo.StopWatchMinute=info->StopWatchMinute;
        LastInfo.StopWatchSeconds=info->StopWatchSeconds;
        LastInfo.StopWatchMilli=info->StopWatchMilli;   
        //done
        break;

    case EDIT:
        break;
    default:
        break;
    }
}
void CLCD_GetUpdates(CLCD_Updates_t * updates)
{

}

/******************************************************************************/