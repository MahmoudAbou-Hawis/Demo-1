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
static uint8_t Last = 0;
bool print  = false;
static uint8_t Second = 0;
static char cursor=1;
static uint8_t currentLine = FIRST_LINE;
static CLCD_info_t temp_info={0} ;
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
    LCD_writeStringAsync(stopwatch+6,6,call);
}
void PrintStopWatchMinute (void)
{
    LCD_writeStringAsync(stopwatch+3,9,call);
}
void PrintStopWatchHour (void)
{
    LCD_writeStringAsync(stopwatch,12,call);
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
    if(Last != 0)
    {
        LCD_clearScreenAsync(call);
        Last = 0;
        return;
    }
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
    if(Last != 1)
    {
        LCD_clearScreenAsync(call);
        Last = 1;
        print = true;
        return;
    }
    convertNumberToString(stopwatch,2,infos->StopWatchHour);
    convertNumberToString(stopwatch+3,2,infos->StopWatchMinute);
    convertNumberToString(stopwatch+6,2,infos->StopWatchSeconds);
    convertNumberToString(stopwatch+9,3,infos->StopWatchMilli);
    if((LastInfo.StopWatchHour != infos->StopWatchHour) || (print))
        LCD_setCursorPosAsync(FIRST_LINE,1,PrintStopWatchHour);
    else if (LastInfo.StopWatchMinute != infos->StopWatchMinute)
        LCD_setCursorPosAsync(FIRST_LINE,4,PrintStopWatchMinute);  
    else if(LastInfo.StopWatchSeconds != infos->StopWatchSeconds)
        LCD_setCursorPosAsync(FIRST_LINE,7,PrintStopWatchSecond);
    else if (LastInfo.StopWatchMilli != infos->StopWatchMilli)
        LCD_setCursorPosAsync(FIRST_LINE,10,PrintStopWatchMilli);
    print = false;
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
    LastInfo.StopWatchHour = 255;
    LastInfo.StopWatchMinute = 255;
    LastInfo.StopWatchMilli = 255;
    LastInfo.StopWatchSeconds = 255;
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
        /*Display and Save Current Data before Editing*/
        
        if(Last != 2 ){
            temp_info.day = info->day;
            temp_info.month = info->month;
            temp_info.year = info->year;
            Second = info->second;
            temp_info.minute = info->minute;
            temp_info.hour = info->hour;
            Last =2;
            cursor = 1 ;
            currentLine = FIRST_LINE;
            LCD_setCursorPosAsync(currentLine, cursor,call);
        }
        
        switch (info->pressedButton)
        {
            

        case RIGHT:
            cursor++;
            if(cursor>=16){
                currentLine = SECOND_LINE;
            }
            break;

        case LEFT:
            cursor--;
            if(cursor<=0){
                cursor =1;
            }
            if((currentLine==SECOND_LINE)&&(cursor<=16)){
                currentLine =FIRST_LINE;
            }
            break;
        case UP:
            break;
        case DOWN:
            break;
        default:
            break;

        }

        LCD_setCursorPosAsync(currentLine,(cursor%16)+1,call);
        /*Not pressed*/
        info->pressedButton = NO_PRESSED;
        break;
    default:
        break;
    }
}
void CLCD_GetUpdates(CLCD_Updates_t * updates)
{


}

/******************************************************************************/