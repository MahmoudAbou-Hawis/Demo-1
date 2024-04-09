#ifndef DATE_H 
#define DATE_H

#include <stdint.h>  
#include <stddef.h> 


/** @brief Enumerated type for date operations (increase or decrease). */
typedef enum Operation {
    INCREASE,
    DECREASE
} Operation_t;

/** @brief Enumerated type for the type of date component to modify. */
typedef enum DateType {
    DAY,
    MONTH,
    YEAR
} DateType_t;

/** @brief Enumerated type for error status during date operations. */
typedef enum DateError {
    DATE_NULL_PTR_PASSED = -1,  /*< Indicate error with negative value */
    DATE_OK = 0,                /*< Success status */
    DATE_INVALID_VALUE          /*< More specific error for invalid date values (not implemented yet) */
} DateError_t;

/** @brief Structure to represent a date. */
typedef struct Date {
    uint32_t day;
    uint32_t month;
    uint32_t year;
} Date_t;

/** @brief Sets the date value based on the specified operation and type.
 *
 *  @param Date The new date.
 *  @return Returns an error code (DATE_NULL_PTR_PASSED or DATE_INVALID_VALUE) on failure,
 *          or DATE_OK on success. (Error handling could be improved)
 */
DateError_t Date_SetDate(Date_t *  Date);

/** @brief Retrieves the current date value.
 *
 *  @param date A pointer to a Date structure to store the retrieved date.
 *  @return Returns an error code (DATE_NULL_PTR_PASSED) on failure,
 *          or DATE_OK on success. (Error handling could be improved)
 */
DateError_t Date_GetDate(Date_t *date);

/** @brief Updates the date . */
void Date_UpdateDate(void);

#endif