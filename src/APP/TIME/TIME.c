#include "TIME.h"
#include "TIME_CFG.h"

/*    inccrement second and minute and hour */
#define INC_SECOND 1
#define INC_MINUTE 1
#define INC_HOUR   1

/* decrement second and minute and hour */
#define DEC_SECOND -1  
#define DEC_MINUTE -1
#define DEC_HOUR   -1

#define IS_STATE_VALIDE(STATE) ((STATE==INCREMENT)||(STATE==DECREMENT))

static  u32 counter ;


static time_t current_time={
    .second=DEFAULT_SECOND,
    .minute=DEFAULT_MINUTE,
    .hour=DEFAULT_HOUR
};

RetTimeError set_time(state_t state , type_t type)
{
    RetTimeError Loc_TimeError=time_ok;
    if (IS_STATE_VALIDE(state))
    {
        switch (type)
        {
        case SECOND:
            current_time.second+=(state==INCREMENT?INC_SECOND:DEC_SECOND);
            break;
        case MINUTE:
            current_time.minute+=(state==INCREMENT?INC_MINUTE:DEC_MINUTE);
        case HOUR:
            current_time.hour+=(state==INCREMENT?INC_HOUR:DEC_HOUR);    
        default:
            break;
        }
    }
    else
    {
        RetTimeError Loc_TimeError=invalid_input;
    }
    
return Loc_TimeError;}

RetTimeError get_time(time_t * time)
{
    RetTimeError LocTimeError=time_ok;
    if (time!=NULL)
    {
       time->second=current_time.second;
       time->minute=current_time.minute;
       time->hour=current_time.hour;
    }
    else
    {
        LocTimeError=invalid_input;
    }
return LocTimeError; }


void update_time(void)
{
    counter+=UPDATE_TICK;
    if(counter==TIME_ONE_SECOND)
    {
        if (current_time.second<NUM_OF_SCONDS)
        {
            current_time.second++;
        }
        else
        {
            if (current_time.minute<NUM_OF_MINUTES)
            {
               current_time.minute++; 
            }
            else
            {
                current_time.hour<NUM_OF_HOURS?current_time.hour++:(current_time.hour=DEFAULT_HOUR);
            }
            
        }
    counter=0;    
    }


}

