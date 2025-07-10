/* Hardware defintions for the respective baord including handles und pin defintions */


#ifndef HARDWARE_DEFINITIONS_H
#define HARDWARE_DEFINITIONS_H
#include <tuple>
#include <cstdint>
#include "../Common/Hardware_handles.h"
#include "STM32F0_Pins_config.h"



extern TIM_HandleTypeDef htim3;
extern CAN_HandleTypeDef hcan;

class HardwareDefinitions
{

private:

UART_HandleTypeDef huart2;

HardwareHandles hwHandles = 
{
    .can = &hcan,
    .timer = &htim3,
    .uart = &huart2,
    .canInitFunc = MX_CAN_Init
};


public:
const HardwareHandles* GetHardwareHandles();


static void MX_CAN_Init(uint16_t baud);



};









#endif // HARDWARE_DEFINITIONS_H




