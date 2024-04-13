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
#include "CSwitch.h"
#include "Date.h"
#include "time.h"
#include "LCD_Control.h"
#include "StopWatch.h"
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
static CSWITCH_ScreenState_t screenState = 
{
    .button             = NO_PRESSED,
    .isStopWatchWorking = NOT_WORKING,
    .state              = NORMAL 
};
static uint8_t count              = 0;
static Date_t date                = {0};
static time_t time                = {0};
static StopWatchTime_t  stopWatch = {0};
static CLCD_info_t ScreenInfo     = {0};
static CLCD_Updates_t Update      = {0}; 
/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

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
void MainApp(void);
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/
void MainApp(void)
{
    CSWITCH_SendUpdate();
    CSWITCH_ReceivedUpdate(&screenState);
    CLCD_GetUpdates(&Update);
    if(Update.isTimeUpdate == true)
    {
        time.hour   = Update.hour;
        time.minute = Update.minute;
        time.second = Update.second; 
        set_time(&time);
        Update.isTimeUpdate = false;
    }
    if(Update.isDateUpdate == true)
    {
        date.day   = Update.day;
        date.month = Update.month;
        date.year  = Update.year; 
        Date_SetDate(&date);
        Update.isDateUpdate = false;
    }
    update_time();
    get_time(&time);
    if(time.hour == 0 && time.minute == 0 &&time.second == 0)
    {
        if(count == 0)
             Date_UpdateDate();
        count++;
    }
    else 
    {
        count = 0;
    }
    if(screenState.isStopWatchWorking == WORKING)
    {
        STOPWATCH_Update();
    }
    else if(screenState.isStopWatchWorking == CLEAR)
    {
        STOPWATCH_Reset();
    }

    Date_GetDate(&date);
    STOPWATCH_GetTime(&stopWatch);
    ScreenInfo.day              = date.day;
    ScreenInfo.year             = date.year;
    ScreenInfo.month            = date.month;
    ScreenInfo.second           = time.second;
    ScreenInfo.minute           = time.minute;
    ScreenInfo.hour             = time.hour;
    ScreenInfo.pressedButton    = screenState.button;
    ScreenInfo.state            = screenState.state;
    ScreenInfo.StopWatchHour    = stopWatch.hour;
    ScreenInfo.StopWatchMinute  = stopWatch.minute;
    ScreenInfo.StopWatchSeconds = stopWatch.second;
    CLCD_Write(&ScreenInfo);
}
/******************************************************************************/