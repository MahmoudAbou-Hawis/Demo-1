/**
 * @file Date.c
 * @brief Implementation file for date manipulation functions.
 */

#include "Date.h"
#include "Date_CFG.h"

/** @brief Definitions of constants for date manipulation */
#define INCREASE_DAY_BY_ONE    1 /**< Increment day by one */
#define DECREASE_DAY_BY_ONE   -1 /**< Decrement day by one */

#define INCREASE_MONTH_BY_ONE  1 /**< Increment month by one */
#define DECREASE_MONTH_BY_ONE -1 /**< Decrement month by one */

#define INCREASE_YEAR_BY_ONE   1 /**< Increment year by one */
#define DECREASE_YEAR_BY_ONE  -1 /**< Decrement year by one */

#define DAYS_IN_MONTH_31 31 /**< Number of days in a month with 31 days */
#define DAYS_IN_MONTH_30 30 /**< Number of days in a month with 30 days */
#define DAYS_IN_FEBRUARY_LEAP 29 /**< Number of days in February during a leap year */
#define DAYS_IN_FEBRUARY_NON_LEAP 28 /**< Number of days in February during a non-leap year */

#define IS_VALID_OPERATION(_Operation) ((_Operation == INCREASE) || (_Operation == DECREASE)) /**< Check if operation is valid */
#define IS_VALID_TYPE(_TYPE) ((_TYPE == DAY) || (_TYPE == MONTH) || (_TYPE == YEAR)) /**< Check if date type is valid */
#define IS_NOT_NULL_PTR(_PTR)   ((_PTR != NULL)) /**< Check if pointer is not null */
#define IS_LEAP_YEAR(year) ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) /**< Check if year is a leap year */

/** @brief Enum for months */
typedef enum {
    JANUARY = 1, /**< January */
    FEBRUARY, /**< February */
    MARCH, /**< March */
    APRIL, /**< April */
    MAY, /**< May */
    JUNE, /**< June */
    JULY, /**< July */
    AUGUST, /**< August */
    SEPTEMBER, /**< September */
    OCTOBER, /**< October */
    NOVEMBER, /**< November */
    DECEMBER /**< December */
} DaysInMonth;

/** @brief Static variables */
static Date_t Current_date = {
    .day   = DEFAULT_DAY,
    .month = DEFAULT_MONTH,
    .year  = DEFAULT_YEAR
};

/** @brief Function to set date */
DateError_t Date_SetDate(Date_t * Date)
{
    DateError_t RET_ErrorStatus = DATE_OK;
    if(Date != NULL)
    {
        Current_date.day = Date->day;
        Current_date.month = Date->month;
        Current_date.year = Date->year;
    }
    else 
    {
        RET_ErrorStatus = DATE_NULL_PTR_PASSED;
    }
    return RET_ErrorStatus;
}

/** @brief Function to get date */
DateError_t Date_GetDate(Date_t * date)
{
    DateError_t RET_ErrorStatus = DATE_OK;
    if (IS_NOT_NULL_PTR(date)) {
        date->day   = Current_date.day;
        date->year  = Current_date.year;
        date->month = Current_date.month;
    } else {
        RET_ErrorStatus = DATE_NULL_PTR_PASSED;
    }
    return RET_ErrorStatus;
}

/** @brief Function to update date */
void Date_UpdateDate(void)
{
    Current_date.day += INCREASE_DAY_BY_ONE;
    if (Current_date.day > 28) {
        switch (Current_date.month) {
        case JANUARY:
        case MARCH:
        case MAY:
        case JULY:
        case AUGUST:
        case OCTOBER:
        case DECEMBER:
            Current_date.day = (Current_date.day > DAYS_IN_MONTH_31) ? 0 : Current_date.day;
            break;
        case FEBRUARY:
            if (IS_LEAP_YEAR(Current_date.year)) {
                Current_date.day = (Current_date.day > DAYS_IN_FEBRUARY_LEAP) ? 0 : Current_date.day;
            } else {
                Current_date.day = (Current_date.day > DAYS_IN_FEBRUARY_NON_LEAP) ? 0 : Current_date.day;
            }
            break;
        default:
            Current_date.day = (Current_date.day > DAYS_IN_MONTH_30) ? 0 : Current_date.day;
            break;
        }
        Current_date.month += ((Current_date.day == 0) ? ++Current_date.day : 0);
        Current_date.month %= 13;
        Current_date.year += ((Current_date.month == 0) ? ++Current_date.month : 0);
    }
}
