#ifndef TIME_H_
#define TIME_H_


#define NULL ((void *)0)


#define TIME_ONE_SECOND 1000    // one second =1000ms 
#define NUM_OF_SCONDS    60      // numbaer of secondes =60 secondes in a minute
#define NUM_OF_MINUTES   60      // numbaer of minutes =60 minutes in an hour
#define NUM_OF_HOURS     24      // numbaer of hours =24  in acday



typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct 
{
   u8 second;
   u8 minute;
   u8 hour; 

}time_t;

// state refere to increment or decrement 
typedef enum{
    INCREMENT,
    DECREMENT

}state_t; 


typedef enum{
   
   SECOND,
   MINUTE,
   HOUR

}type_t;


typedef enum{
    
    time_ok,
    invalid_input

}RetTimeError;

/** @brief Sets the time value based on the specified operation and type.
 *
 *  @param time refer to the new time.
 *  @return Returns an error code (time_ok or invalid_input) on failure.
 */
RetTimeError set_time(time_t *time);

/** @brief Retrieves the current time.
 *
 *  @param time Pointer to a time_t structure to store the retrieved time.
 *  @return Returns an error code (time_ok or invalid_input) on failure.
 */

RetTimeError get_time(time_t * time);


/** @brief Updates the current time based on the elapsed time.
 *  
 *  This function should be called periodically to update the time.
 *  It increments the seconds and adjusts minutes and hours accordingly.
 */

void update_time(void);


#endif