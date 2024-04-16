/*******************************************************************************/
/**
 * @file LCD_Control.h
 * @brief Header file for LCD control functionality.
 *
 * @par Project Name
 * 
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file contains declarations for functions and structures related to LCD control.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef LCD_CONTROL_H_
#define LCD_CONTROL_H_
/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "CSwitch.h" /**< Assuming this is a custom header file for switch functionality */
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/
/**
 * @brief Structure to represent LCD information.
 */
typedef struct 
{
    CSWITCH_States_t        state; /**< State of the LCD */
    CSWITCH_PressedButton_t pressedButton; /**< Pressed button */
    uint8_t                 second; /**< Second value */
    uint8_t                 minute; /**< Minute value */
    uint8_t                 hour; /**< Hour value */
    uint32_t                day; /**< Day value */
    uint32_t                month; /**< Month value */
    uint32_t                year; /**< Year value */ 
    uint32_t                StopWatchMilli; /**< Milliseconds value for stopwatch */
    uint32_t                StopWatchSeconds; /**< Seconds value for stopwatch */
    uint32_t                StopWatchHour; /**< Hours value for stopwatch */
    uint32_t                StopWatchMinute; /**< Minutes value for stopwatch */
} CLCD_info_t;

/**
 * @brief Structure to represent LCD updates.
 */
typedef struct 
{
    bool isDateUpdate; /**< Flag indicating whether date is updated */
    bool isTimeUpdate; /**< Flag indicating whether time is updated */
} CLCD_Updates_t;


/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DECLARATIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DECLARATIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES */
/******************************************************************************/

/**
 * @brief Initializes the LCD.
 */
void CLCD_Init(void);

/**
 * @brief Writes LCD information.
 * 
 * @param info Pointer to the LCD information structure.
 */
void CLCD_Write(CLCD_info_t *info);

/**
 * @brief Retrieves updates from the LCD.
 * 
 * @param updates Pointer to the LCD updates structure.
 */
void CLCD_GetUpdates(CLCD_Updates_t *updates);

/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus
}
#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#endif /* LCD_CONTROL_H_ */
/******************************************************************************/
