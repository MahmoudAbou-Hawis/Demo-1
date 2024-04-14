#include "CSwitch.h"
#include "Sched.h"
#include "LCD_Control.h"

int main()
{
    CSWITCH_Init();	
    CLCD_Init();
    Sched_init();
    Sched_Start();
    return 0;
}