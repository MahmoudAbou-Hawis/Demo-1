/******************************************************************************/
/**
 * @file switches_control.c
 * @brief Switch Control Module with Clock State Information
 *
 * @par Project Name
 * Switch Control System
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file contains the implementation of a module to control switches and 
 * provide clock state information over UART using a custom control protocol.
 * 
 * The module receives commands over UART to inquire about the current clock
 * state (Edit, Stopwatch, Normal), which is communicated using a custom
 * control protocol. Additionally, it accepts commands to turn switches on/off
 * and to request their status. It implements functions to control switches
 * and to retrieve their status based on the provided commands.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "HSW.h"
#include "ControlProtocol.h"
#include "CSwitch.h"
#include "HSW_confg.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/** the clock state of the another system */
static CSWITCH_States_t state = NORMAL;

/** the clock state of the  system */
static CSWITCH_States_t MyState = NORMAL;

/** Carry the button which pressed */
static CSWITCH_PressedButton_t MyPbutton = NO_PRESSED;

/** Message used to receive the commends from the another system*/
static Message_t Mymsg;
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/


/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

/**Used to know the total time switch pressed*/
static uint8_t UPNumberOfPressed = 0;

/**to calculate the total time  */
static uint32_t UPCounts = 0;

/**Used to know the total time switch pressed*/
static uint8_t DownNumberOfPressed = 0;

/**to calculate the total time  */
static uint32_t DOWNCounts = 0;

/** catch the stopwatch state */
static CSWITCH_StopWatchState_t isStopWatchWorking = NOT_WORKING;
/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION PROTOTYPES */
/******************************************************************************/

/**
 * @brief Used to control switches in the normal mode.
 * @return None
 */
static void CheckButtonsInNormalState(void);

/**
 * @brief Used to control switches in the StopWatch mode.
 * @return None
 */
static void CheckButtonsInStopWatchState(void);


/**
 * @brief Used to control switches in the Edit mode.
 * @return None
 */
static void CheckButtonsInEditState(void);

/**
 * @brief used by control protocol when it received new command.
 */
static void ReceiveCallBack(void);

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/
static void CheckButtonsInNormalState(void)
{
    uint32_t ButtonRead;
    Message_t msg;
    msg.MessageType = COMMAND;
    msg.CallBack =  NULL;
    msg.len = 1;
    SWITCH_enuGetStatus(UP_SWITCH,&ButtonRead);
    if(ButtonRead == PRESSED)
    {
        state = STOPWATCH;
        msg.pMessage[0] = 'S';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(DOWN_SWITCH,&ButtonRead);
    if(ButtonRead == PRESSED)
    {
        state = EDIT;
        msg.pMessage[0] = 'E';
        Protocol_SendAsync(&msg);
    }
}

static void CheckButtonsInStopWatchState(void)
{
    uint32_t ButtonRead;
    Message_t msg;
    msg.MessageType = COMMAND;
    msg.pMessage[0] = 'S';
    msg.CallBack =  NULL;
    msg.len = 2;
    SWITCH_enuGetStatus(UP_SWITCH,&ButtonRead);
    /** Go to start the stopwatch */
    if(ButtonRead == PRESSED)
    {
        isStopWatchWorking = WORKING;
        msg.pMessage[1] = 'G';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(RIGHT_SWITCH,&ButtonRead);
    /**Pause the stopwatch*/
    if(ButtonRead == PRESSED)
    {
        isStopWatchWorking = NOT_WORKING;
        msg.pMessage[1] = 'P';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(DOWN_SWITCH,&ButtonRead);
    /**reset the stopwatch*/
    if(ButtonRead == PRESSED)
    {
        msg.pMessage[1] = 'Z';
        isStopWatchWorking = RESET;
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(LEFT_SWITCH,&ButtonRead);
    /** Go to the normal mode */
    if(ButtonRead == PRESSED)
    {
        msg.len = 1; 
        msg.pMessage[0] = 'N';
        msg.pMessage[1] = 0;
        Protocol_SendAsync(&msg);
        state = NORMAL;
        return;
    }
}


static void CheckButtonsInEditState(void)
{
    uint32_t ButtonRead;
    Message_t msg;
    msg.MessageType = COMMAND;
    msg.CallBack =  NULL;
    msg.len = 2;
    msg.pMessage[0] = 'E';
    UPCounts += 100;
    DOWNCounts += 100;
    SWITCH_enuGetStatus(UP_SWITCH,&ButtonRead);
    if(ButtonRead == PRESSED) UPNumberOfPressed++;
    if(UPCounts >= 1600)
    {
        UPCounts = 0;
        /** increase the value which the cursor in*/
        if(UPNumberOfPressed >= 1 && UPNumberOfPressed < 5)
        {
            msg.pMessage[1] = 'U';
            Protocol_SendAsync(&msg);
            UPNumberOfPressed = 0;
            return;
        }
        /** Accept the edition*/
    	else if(UPNumberOfPressed >= 6)
		{
            msg.pMessage[0] = 'N';
            msg.pMessage[1] = 'K';
            Protocol_SendAsync(&msg);
            state = NORMAL;
            UPNumberOfPressed = 0;
            return;
		}
    }
    SWITCH_enuGetStatus(DOWN_SWITCH,&ButtonRead);
    if(ButtonRead == PRESSED) DownNumberOfPressed++;
    if(DOWNCounts >= 1600)
    {
        /** Decrease the value which the cursor in*/
        if(DownNumberOfPressed >= 1 && DownNumberOfPressed < 5)
        {
            msg.pMessage[1] = 'D';
            Protocol_SendAsync(&msg);
            DownNumberOfPressed = 0;
            return;
        }
    	else if(DownNumberOfPressed >= 6)
		{
            /**Quit the the edition and cancel it*/
            msg.pMessage[1] = 'Q';
            msg.pMessage[0] = 'N';
            state = NORMAL;
            DownNumberOfPressed = 0;
            Protocol_SendAsync(&msg);
            return;
		}
        DownNumberOfPressed  = 0;
        DOWNCounts = 0;
    }
    SWITCH_enuGetStatus(RIGHT_SWITCH,&ButtonRead);
    if(ButtonRead == PRESSED)
    {
        /** go with the cursor right */
        msg.pMessage[1] = 'R';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(LEFT_SWITCH,&ButtonRead);
    if(ButtonRead == PRESSED)
    {
     /** go with the cursor left */
        msg.pMessage[1] = 'L';
        Protocol_SendAsync(&msg);
        return;
    }
}

void ReceiveCallBack(void)
{
    /** go to the Normal mode */
    if(Mymsg.pMessage[0] == 'N')
    {
        MyState = NORMAL;
    }
    /** go to the Edit mode */
    else if(Mymsg.pMessage[0] == 'E')
    {
        MyState = EDIT;
    }
    /** go to the stop mode */
    else if(Mymsg.pMessage[0] == 'S')
    {
        MyState = STOPWATCH;
    }
    if(Mymsg.len == 2)
    {
        /** start the stopwatch */
        if(Mymsg.pMessage[1] == 'G')
        {
            MyPbutton = GO;
        }
        /** move the cursor left */
        else if(Mymsg.pMessage[1] == 'L')
        {
            MyPbutton =  LEFT;
        }
        /** move the cursor right */
        else if(Mymsg.pMessage[1] == 'R')
        {
            MyPbutton = RIGHT;
        }
        /** quit the edit mode without update the editions */
        else if(Mymsg.pMessage[1] == 'Q')
        {
            MyPbutton = CANCEL;
        }
        /** quit the edit mode with update the editions */
        else if(Mymsg.pMessage[1] == 'K')
        {
            MyPbutton = OK;
        }
        /** increase the value which cursor in */
        else if(Mymsg.pMessage[1] == 'U')
        {
            MyPbutton = UP;
        }
        /** Decrease the value which cursor in */
        else if(Mymsg.pMessage[1] == 'D')
        {
            MyPbutton = DOWN;
        }
        /** pause the stopwatch */
        else if(Mymsg.pMessage[1] == 'P')
        {
            MyPbutton = PAUSE;
        }
        /** reset the stopwatch */
        else if(Mymsg.pMessage[1] == 'Z')
        {
            MyPbutton = RESET;
        }
    }
}

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/
void CSWITCH_Init(void)
{
    Protocol_Init();
	SW_init();
    Mymsg.CallBack = ReceiveCallBack;
    Protocol_ReceiveAsync(&Mymsg);
}

void CSWIRCH_SendUpdate(void)
{
    switch (state)
    {
    case NORMAL:
        CheckButtonsInNormalState();
        break;
    case STOPWATCH:
        CheckButtonsInStopWatchState();
        break;
    case EDIT:
        CheckButtonsInEditState();
        break;
    default:
        break;
    }
}

CSWITCH_ErrorStatus_t CSWIRCH_ReceivedUpdate(CSWITCH_ScreenState_t * Updates)
{
    CSWITCH_ErrorStatus_t RET_ErrorStatus = CSWITCH_OK;
    if(Updates != NULL)
    {
        Updates->button = MyPbutton;
        Updates->state  = MyState;
        Updates->isStopWatchWorking = isStopWatchWorking;
    }
    else
    {
        RET_ErrorStatus = CSWITCH_NULL_PTR_PASSES;
    }
    return  RET_ErrorStatus;
}

/******************************************************************************/