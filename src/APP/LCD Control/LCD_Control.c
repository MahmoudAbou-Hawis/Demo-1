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
static char cursor=26;
static uint8_t currentLine = SECOND_LINE;
static CLCD_info_t temp_info={0} ;
extern CSWITCH_PressedButton_t MyPbutton;
static uint8_t updateTime =0;
static uint8_t updateDate =0;
static  uint8_t edit;

typedef enum{
    Psecond,
    Pminute,
    Phour,
    Pday,
    Pmonth,
    Pyear,
}Edit_Mode;
/*
2-3 hou
5-6 min
yEAR 16 17 18 19
MO   22 21
day 24-25

*/
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
                updateDate++;
                info->day++;
                if(info->day ==30){
                    info->day =0;
                }
                break;
            case Pmonth:
                updateDate++;
                info->month++;
                if(info->month ==12){
                    info->month =0;
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
                if(info->day ==255){
                    info->day =30;
                }
                break;
            case Pmonth:
                updateDate++;
                info->month--;
                if(info->month ==255){
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

            
            info->minute = temp_info.minute + Second/60;
            if(info->minute >=60){
               
                info->hour +=  info->minute/60;
                 info->minute %=60;
            }

            info->state =NORMAL;
            MyPbutton = NO_PRESSED;
            break;
        case OK:
            info->state = NORMAL;
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