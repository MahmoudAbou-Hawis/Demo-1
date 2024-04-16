/**
 * @file Time.h
 * @brief Header file for time functionality.
 *
 * This file contains declarations for functions and structures related to time management.
 */

#ifndef TIME_H_
#define TIME_H_

#define NULL ((void *)0)

#define TIME_ONE_SECOND 1000    /**< One second in milliseconds */
#define NUM_OF_SECONDS  60      /**< Number of seconds in a minute */
#define NUM_OF_MINUTES  60      /**< Number of minutes in an hour */
#define NUM_OF_HOURS    24      /**< Number of hours in a day */

typedef unsigned char u8;  /**< 8-bit unsigned integer */
typedef unsigned short u16; /**< 16-bit unsigned integer */
typedef unsigned int u32;   /**< 32-bit unsigned integer */

/**
 * @brief Structure to represent time.
 */
typedef struct 
{
   u8 second; /**< Second */
   u8 minute; /**< Minute */
   u8 hour; /**< Hour */
} time_t;

// State refers to increment or decrement 
typedef enum{
    INCREMENT, /**< Increment state */
    DECREMENT /**< Decrement state */
} state_t; 

typedef enum{
   SECOND, /**< Second type */
   MINUTE, /**< Minute type */
   HOUR /**< Hour type */
} type_t;

typedef enum{
    time_ok, /**< No error */
    invalid_input /**< Invalid input error */
} RetTimeError;

/** 
 * @brief Sets the time value based on the specified operation and type.
 * 
 * @param time Pointer to the new time.
 * @return Returns an error code (time_ok or invalid_input) on failure.
 */
RetTimeError set_time(time_t *time);

/** 
 * @brief Retrieves the current time.
 * 
 * @param time Pointer to a time_t structure to store the retrieved time.
 * @return Returns an error code (time_ok or invalid_input) on failure.
 */
RetTimeError get_time(time_t *time);

/** 
 * @brief Updates the current time based on the elapsed time.
 * 
 * This function should be called periodically to update the time.
 * It increments the seconds and adjusts minutes and hours accordingly.
 */
void update_time(void);

#endif
