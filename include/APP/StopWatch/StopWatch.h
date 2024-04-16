/**
 * @file Stopwatch.h
 * @brief Header file for stopwatch functionality.
 *
 * This file contains declarations for functions and structures related to stopwatch control.
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <stdint.h>  
#include <stddef.h> 
#include "StopWatch_Confg.h" /**< Assuming this is a custom header file for stopwatch configuration */

#define STOP_TIME_ONE_SECOND 1000    /**< One second in milliseconds */
#define NUM_OF_SECONDS       60      /**< Number of seconds in a minute */
#define NUM_OF_MINUTES       60      /**< Number of minutes in an hour */
#define NUM_OF_HOURS         24      /**< Number of hours in a day */
#define DEFAULT              0       /**< Default value */

/**
 * @brief Structure to represent stopwatch time.
 */
typedef struct 
{
   uint16_t milli; /**< Milliseconds */
   uint16_t second; /**< Seconds */
   uint16_t minute; /**< Minutes */
   uint16_t hour; /**< Hours */
} StopWatchTime_t;

/**
 * @brief Enumeration for stopwatch error codes.
 */
typedef enum{
    StopWatch_enumOk, /**< No error */
    StopWatch_NullPointer, /**< Null pointer error */
} StopWatch_Error;

/**
 * @brief Reset the stopwatch.
 *
 * This function resets the stopwatch to its initial state.
 */
void STOPWATCH_Reset(void);

/**
 * @brief Updates the stopwatch time based on the elapsed time.
 * 
 * This function should be called periodically to update the time of the stopwatch.
 * It increments the seconds and adjusts minutes and hours accordingly.
 */
void STOPWATCH_Update(void);

/**
 * @brief Retrieves the current time of the stopwatch.
 * 
 * @param time Pointer to a StopWatchTime_t structure to store the retrieved time.
 * @return Returns an error code (StopWatch_enumOk or StopWatch_NullPointer) on failure.
 */
StopWatch_Error STOPWATCH_GetTime(StopWatchTime_t *time);

#endif   /* STOPWATCH_H_ */
