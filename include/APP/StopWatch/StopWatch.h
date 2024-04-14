#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <stdint.h>  
#include <stddef.h> 
#include "StopWatch_Confg.h"



#define STOP_TIME_ONE_SECOND     1000    // one second =1000ms 
#define NUM_OF_SCONDS       60      // numbaer of secondes =60 secondes in a minute
#define NUM_OF_MINUTES      60      // numbaer of minutes =60 minutes in an hour
#define NUM_OF_HOURS        24      // numbaer of hours =24  in acday
#define DEFAULT             0

typedef struct 
{
   uint16_t milli;
   uint16_t second;
   uint16_t minute;
   uint16_t hour; 

}StopWatchTime_t;


typedef enum{
    StopWatch_enumOk,

    StopWatch_NullPointer,
}StopWatch_Error;

/*
 @brief  Reset Stop Watch. 
 */

void STOPWATCH_Reset(void);
/* 
 *@brief Updates the stop watch time based on the elapsed time. 
 *  This function should be called periodically to update the time of the stop watch.
 *  It increments the seconds and adjusts minutes and hours accordingly.
 */
void STOPWATCH_Update(void);

/* 
 *  @brief Retrieves the current time of stop watch.
 *  @param time Pointer to a StopWatchTime_t structure to store the retrieved time.
 *  @return Returns an error code (StopWatch_enumOk or StopWatch_NullPointer) on failure.
 */
StopWatch_Error STOPWATCH_GetTime(StopWatchTime_t *time);

#endif   /*STOPWATCH_H_*/


