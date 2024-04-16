#ifndef DATE_H 
#define DATE_H

#include <stdint.h>  
#include <stddef.h> 

/**
 * @file date.h
 * @brief This file contains structures and functions related to date operations.
 */

/** @brief Enumerated type for date operations (increase or decrease). */
typedef enum Operation {
    INCREASE, /**< Increase operation */
    DECREASE /**< Decrease operation */
} Operation_t;

/** @brief Enumerated type for the type of date component to modify. */
typedef enum DateType {
    DAY, /**< Day component */
    MONTH, /**< Month component */
    YEAR /**< Year component */
} DateType_t;

/** @brief Enumerated type for error status during date operations. */
typedef enum DateError {
    DATE_NULL_PTR_PASSED = -1, /**< Indicate error with negative value */
    DATE_OK = 0, /**< Success status */
    DATE_INVALID_VALUE /**< More specific error for invalid date values (not implemented yet) */
} DateError_t;

/** @brief Structure to represent a date. */
typedef struct Date {
    uint32_t day; /**< Day of the month */
    uint32_t month; /**< Month of the year */
    uint32_t year; /**< Year */
} Date_t;

/** 
 * @brief Sets the date value based on the specified operation and type.
 *
 * This function modifies the date value based on the specified operation and type.
 *
 * @param Date A pointer to the Date structure to modify.
 * @return Returns an error code (DATE_NULL_PTR_PASSED or DATE_INVALID_VALUE) on failure, or DATE_OK on success.
 */
DateError_t Date_SetDate(Date_t *Date);

/** 
 * @brief Retrieves the current date value.
 *
 * This function retrieves the current date value and stores it in the provided Date structure.
 *
 * @param date A pointer to a Date structure to store the retrieved date.
 * @return Returns an error code (DATE_NULL_PTR_PASSED) on failure, or DATE_OK on success.
 */
DateError_t Date_GetDate(Date_t *date);

/** 
 * @brief Updates the date.
 *
 * This function updates the current date.
 */
void Date_UpdateDate(void);

#endif
