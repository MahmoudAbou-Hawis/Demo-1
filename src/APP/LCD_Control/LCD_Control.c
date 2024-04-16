/******************************************************************************/
/**
 * @file LCD Control.c 
 * @brief Time Display, Stopwatch, and Edit Functionality
 *
 * This file provides functionalities for a versatile time application
 * offering three modes:
 *  - Stop watch: Tracks elapsed time.
 *  - Normal: Displays the current time and date.
 *  - Edit: Allows modification of the displayed time and date (with security considerations).
 *
 * @par Project Name
 *  Demo 1
 *
 * @par Code Language
 * C
 *
 * @par Description
 * - Implements a basic stopwatch with start, stop, and reset functions.
 * - Displays the current time and date in a user-friendly format (e.g., HH:MM:SS DD/MM/YYYY).
 * - Provides an edit mode for adjusting the displayed time and date.
 *
 * @par Authors
 * Mahmoud Abou-Hawis ,Farma Ezzat ,Amira mahmoud 
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

#define IS_LEAP_YEAR(year) ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
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
static uint32_t Second = 0;
static char cursor=26;
static uint8_t currentLine = SECOND_LINE;
static CLCD_info_t temp_info={0} ;
extern CSWITCH_PressedButton_t MyPbutton;
static uint8_t updateTime =0;
static uint8_t updateDate =0;
static  uint8_t edit;
extern CSWITCH_States_t MyState;
static uint32_t count = 0; 

#include <stdint.h>

uint8_t MonthsDays[13] = {
    0,   /* No month 0, but added to align with month numbers (e.g., January is 1st month) */
    31,  /* January has 31 days */
    28,  /* February has 28 days in a non-leap year */
    31,  /* March has 31 days */
    30,  /* April has 30 days */
    31,  /* May has 31 days */
    30,  /* June has 30 days */
    31,  /* July has 31 days */
    31,  /* August has 31 days */
    30,  /* September has 30 days */
    31,  /* October has 31 days */
    30,  /* November has 30 days */
    31   /* December has 31 days */
};


typedef enum{
    Psecond,
    Pminute,
    Phour,
    Pday,
    Pmonth,
    Pyear,
}Edit_Mode;

Edit_Mode EditMode_Position(void){
    Edit_Mode Return =255;
    //Detect Second
    if((cursor == 8)||(cursor == 7) ){
        Return =Psecond;
        /*Detect Hours*/    
    }else if((cursor == 1)||(cursor == 2)){
        Return = Phour;
        /*Detect Minutes*/ 
    }else if((cursor == 4)||(cursor == 5)){
        Return = Pminute;
        /*Detect Year*/
    }else if((cursor == 15)||(cursor == 17)||(cursor == 18)||(cursor == 16)){
        Return = Pyear;
        /*Detect Month*/
    }else if((cursor == 20)||(cursor == 21)){
        Return = Pmonth;
        /*Detect Day*/
    }else if((cursor == 24)||(cursor == 23)){
        Return = Pday;
    }
    return Return;
}
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
void SetCursorInUserPosition(void);

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
    LCD_writeStringAsync(date,10,SetCursorInUserPosition);
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
void showDateAndTimeInEditMode(void)
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

void SetCursorInUserPosition(void){
        LCD_setCursorPosAsync(currentLine,(cursor%16)+1,call);

}
void showDateAndTimeInNormalMode(void)
{
    if(Last != 0)
    {
        LCD_clearScreenAsync(call);
        Last = 0;
        cursor=26;
        currentLine= SECOND_LINE;
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
       count += 100;
       if(count == 1000)
       {
        Second++;
        count = 0;
       } 
        showDateAndTimeInEditMode();
        if(Last != 2 ){
            temp_info.day = info->day;
            temp_info.month = info->month;
            temp_info.year = info->year;
            Second = info->second;
            temp_info.minute = info->minute;
            temp_info.hour = info->hour;
            cursor=2;
            currentLine= SECOND_LINE;
            Second = 0;
            count = 0;
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
            MyPbutton = NO_PRESSED;
            break;
        case LEFT:
            cursor--;
            if(cursor<=0){
                cursor =1;
            }
            if((currentLine==SECOND_LINE)&&(cursor<16)){
                currentLine =FIRST_LINE;
                cursor = 15;
            }
            MyPbutton = NO_PRESSED;
            break;
        case UP:

            edit = EditMode_Position();
            switch (edit)
            {
            case Psecond:
                updateTime++;
                info->second++;
                if(info->second == 60){
                    info->second =0;       
                }
                break;
            case Pminute:
                updateTime++;
                info->minute++;
                if(info->minute==60){
                    info->minute =0;
                }
                break;    
            case Phour:
                updateTime++;
                info->hour++;
                if(info->hour==24){
                    info->hour =0;
                }
                break;
            case Pday :
                if ((info->day + 1 <= MonthsDays[info->month]) || (info->month == 2 && IS_LEAP_YEAR(info->year) && info->day < 29))
                {
                    updateDate++;
                    info->day++;
                    if(info->day ==30){
                        info->day = 1;
                    }
                }
                break;
            case Pmonth:
                updateDate++;
                info->month++;
                if(info->month ==13){
                    info->month =1;
                }
                break;

            case Pyear:
                updateDate++;
                info->year++;
                break;        
            default:
                break;
            }
            MyPbutton = NO_PRESSED;
            break;
        case DOWN:
            edit = EditMode_Position();
            switch (edit)
            {
            case Psecond:
                updateTime++;
                info->second--;
                if(info->second == 255){
                    info->second =59;       
                }
                break;
            case Pminute:
                updateTime++;
                info->minute--;
                if(info->minute==255){
                    info->minute =59;
                }
                break;    
            case Phour:
                updateTime++;
                info->hour--;
                if(info->hour==255){
                    info->hour =23;
                }
                break;
            case Pday :
                updateDate++;
                info->day--;
                if(info->day ==0){
                    info->day = MonthsDays[info->month];
                    if((IS_LEAP_YEAR(info->year)) && info->month == 2)
                    {
                        info->day  = 29;
                    }
                }
                break;
            case Pmonth:
                updateDate++;
                info->month--;
                if(info->month ==0){
                    info->month =12;
                }
                break;
            case Pyear:
                updateDate++;
                info->year--;
                break;        
            default:
                break;
            }
            MyPbutton = NO_PRESSED;
            break;
        case CANCEL:
            updateTime =1;
            updateDate =1;
            info->year = temp_info.year;
            info->month = temp_info.month;
            info->day = temp_info.day;
            info->second  =Second %60;
            info->hour = temp_info.hour;
            info->minute = temp_info.minute;
            info->minute = temp_info.minute + Second/60;
            if(info->minute >=60){
                info->hour +=  info->minute/60;
                info->minute %=60;
                info->hour%=24;
            }
            MyState =NORMAL;
            MyPbutton = NO_PRESSED;
            break;
        case OK:
            MyState = NORMAL;
             MyPbutton = NO_PRESSED;
            break;    
        default:
            break;

        }
        /*Not pressed*/
        break;
    default:
        break;
    }
}
void CLCD_GetUpdates(CLCD_Updates_t * updates)
{
    if(updateTime!=0){
        updates->isTimeUpdate= true;
        updateTime =0;
    }
    if(updateDate!=0){
        updates->isDateUpdate =true;
        updateDate =0;
    }
}

/******************************************************************************/