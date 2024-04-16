/**
 * @file main.c
 * @brief Main program file
 *
 * @par Project Name
 * Demo 1
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file contains the main function to initialize the switch control module,
 * LCD control module, and the scheduler, and start the scheduler.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */

#include "CSwitch.h"
#include "Sched.h"
#include "LCD_Control.h"

/**
 * @brief Main function
 * 
 * @return Integer indicating the exit status
 */
int main()
{
    /* Initialize the switch control module*/
    CSWITCH_Init();
    
    /* Initialize the LCD control module*/
    CLCD_Init();
    
    /* Initialize the scheduler*/
    Sched_init();
    
    /* Start the scheduler*/
    Sched_Start();
    
    /* Return 0 to indicate successful execution*/
    return 0;
}
