/*
 * File: Date.c
 * Description: Implementation file for date manipulation functions.
 */

#include "Date.h"
#include "Date_CFG.h"

/*@brief Definitions of constants for date manipulation */
#define INCREASE_DAY_BY_ONE    1
#define DECREASE_DAY_BY_ONE   -1

#define INCREASE_MONTH_BY_ONE  1
#define DECREASE_MONTH_BY_ONE -1

#define INCREASE_YEAR_BY_ONE   1
#define DECREASE_YEAR_BY_ONE  -1

#define DAYS_IN_MONTH_31 31
#define DAYS_IN_MONTH_30 30
#define DAYS_IN_FEBRUARY_LEAP 29
#define DAYS_IN_FEBRUARY_NON_LEAP 28

#define IS_VALID_OPERATION(_Operation) ((_Operation == INCREASE) || (_Operation == DECREASE))
#define IS_VALID_TYPE(_TYPE) ((_TYPE == DAY) || (_TYPE == MONTH) || (_TYPE == YEAR))
#define IS_NOT_NULL_PTR(_PTR)   ((_PTR != NULL))
#define IS_LEAP_YEAR(year) ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))

/*@brief Enum for months */
typedef enum {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
} DaysInMonth;

/*@brief Static variables */
static Date_t Current_date = {
    .day   = DEFAULT_DAY,
    .month = DEFAULT_MONTH,
    .year  = DEFAULT_YEAR
};

const static uint32_t DayInMilliSeconds = 86400000;
static uint32_t millisCounter = 0;

/*@brief Function to set date */
DateError_t Date_SetDate(Operation_t operation, DateType_t type)
{
    DateError_t RET_ErrorStatus = DATE_OK;
    if (IS_VALID_OPERATION(operation) && IS_VALID_TYPE(type)) {
        switch (type) {
        case DAY:
            Current_date.day += ((operation == INCREASE) ? INCREASE_DAY_BY_ONE : DECREASE_DAY_BY_ONE);
            break;
        case MONTH:
            Current_date.month = ((operation == INCREASE) ? INCREASE_MONTH_BY_ONE : DECREASE_MONTH_BY_ONE);
            break;
        case YEAR:
            Current_date.month = ((operation == INCREASE) ? INCREASE_YEAR_BY_ONE : DECREASE_YEAR_BY_ONE);
            break;
        default:
            break;
        }
    } else {
        RET_ErrorStatus = DATE_INVALID_VALUE;
    }
    return RET_ErrorStatus;
}

/*@brief Function to get date */
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

/*@brief Function to update date */
void Date_UpdateDate(void)
{
    millisCounter += UPDATE_TICK;
    if (millisCounter == DayInMilliSeconds) {
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
        millisCounter = 0;
    }
}
