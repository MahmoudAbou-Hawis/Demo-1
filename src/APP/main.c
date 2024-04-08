#include "Demo1_LCD.h"
#include "RCC.h"
#include "HSW.h"
#include "./Switch_Control/CSwitch.h"
#include "Sched.h"

void APP_Runnable(void)
{
    CSWIRCH_SendUpdate();
}

int main()
{
    CSWITCH_Init();	

    Sched_init();
    Sched_Start();
    return 0;
}