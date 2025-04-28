#include "stm32c0xx.h"
#include "core_cm0.h"
//#include "FreeRTOS.h"

void HardFault_Handler()
{
    //__asm("bkpt");
    //portDISABLE_INTERRUPTS();
    while(1);
}
