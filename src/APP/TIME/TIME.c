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

RetTimeError set_time(time_t * time)
{
    RetTimeError RET_ErrorStatus = time_ok;
    if(time != NULL)
    {
        current_time.hour   = time->hour;
        current_time.minute = time->minute;
        current_time.second = time->second ;
    }
    else
    {
        RET_ErrorStatus = invalid_input;
    }
    return RET_ErrorStatus;
}

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
    if(counter == TIME_ONE_SECOND)
    {
        current_time.second++;
        current_time.second %= NUM_OF_SCONDS;
        current_time.minute += ((current_time.second == 0)?INC_MINUTE:0);
        current_time.hour   += ((current_time.minute == NUM_OF_MINUTES)?INC_HOUR:0);
        current_time.minute %= (NUM_OF_MINUTES);
        current_time.hour   %= NUM_OF_HOURS;
        counter=0;    
    }
}

