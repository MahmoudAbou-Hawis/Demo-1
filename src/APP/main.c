#include "Demo1_LCD.h"
#include "RCC.h"
#include "HSW.h"
#include "CSwitch.h"
#include "Sched.h"
#include "LCD_Control.h"
#include "ControlProtocol.h"

int main()
{
    CSWITCH_Init();	
    CLCD_Init();
    Sched_init();
    Sched_Start();
    return 0;
}