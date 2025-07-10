

#ifndef HARDWARE_HANDLES_H
#define HARDWARE_HANDLES_H

#include <array>

struct HardwareHandles 
{

    #ifdef FDCAN1
    FDCAN_HandleTypeDef* can;
    #else
    CAN_HandleTypeDef* can;
    #endif

    TIM_HandleTypeDef* timer;
    UART_HandleTypeDef* uart;
    void (*canInitFunc)(uint16_t baud);
};





#endif // HARDWARE_HANDLES_H
