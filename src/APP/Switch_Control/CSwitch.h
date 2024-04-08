/******************************************************************************/
/**
 * @file switches_module.h
 * @brief Header File for Switch Control Module with Clock State Information
 *
 * @par Project Name
 * Embedded Switch Control System
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file declares the interface for a module to control switches and 
 * provide clock state information over UART using a custom control protocol.
 * 
 * The module defines enums for different states of the clock (Edit, Stopwatch,
 * Normal) and button presses, as well as structs to hold screen state 
 * information. It also declares functions for module initialization, sending
 * updates, and receiving updates.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef SWITCHES_MODULE_H_
#define SWITCHES_MODULE_H_
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

/** Enum for error status */
typedef enum
{
    CSWITCH_NULL_PTR_PASSES, /**< Null pointer passed */
    CSWITCH_WRONG,           /**< Wrong value or operation */
    CSWITCH_OK               /**< Operation successful */
} CSWITCH_ErrorStatus_t;

/** Enum for clock states */
typedef enum
{
    STOPWATCH,   /**< Stopwatch mode */
    EDIT,        /**< Edit mode */
    NORMAL       /**< Normal mode */
} CSWITCH_States_t;

/** Enum for pressed buttons */
typedef enum
{
    UP,         /**< Up button pressed */
    RIGHT,      /**< Right button pressed */
    LEFT,       /**< Left button pressed */
    DOWN,       /**< Down button pressed */
    CANCEL,     /**< Cancel button pressed */
    OK,         /**< OK button pressed */
    GO,         /**< Go button pressed */
    PAUSE,      /**< Pause button pressed */
    RESET,      /**< Reset button pressed */
    NO_PRESSED  /**< No button pressed */
} CSWITCH_PressedButton_t;

/** Enum for stopwatch status */
typedef enum
{
    NOT_WORKING, /** StopWatch is Not Working */
    WORKING,     /** StopWatch is Working */
    CLEAR        /** Clear the stop Watch */
} CSWITCH_StopWatchState_t;
/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/** Struct to hold screen state information */
typedef struct 
{
    CSWITCH_States_t state;                          /**< Current state of the clock */
    CSWITCH_PressedButton_t button;                  /**< Last pressed button */
    CSWITCH_StopWatchState_t isStopWatchWorking;     /**< Flag indicating if stopwatch is active */
} CSWITCH_ScreenState_t;


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
 * @brief Initialize the switches module
 */
extern void CSWITCH_Init(void);

/**
 * @brief Send update over UART
 */
extern void CSWIRCH_SendUpdate(void);

/**
 * @brief Receive update over UART
 * 
 * @param Updates Pointer to structure to hold received updates
 * @return CSWITCH_ErrorStatus_t Error status of the operation
 */
extern CSWITCH_ErrorStatus_t CSWIRCH_ReceivedUpdate(CSWITCH_ScreenState_t * Updates);


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
#endif /* SWITCHES_MODULE_H_ */
/******************************************************************************/

