/* Hardware defintions for the respective baord including handles und pin defintions */


#ifndef HARDWARE_DEFINITIONS_H
#define HARDWARE_DEFINITIONS_H
#include <tuple>
#include <cstdint>
#include "../Common/Hardware_handles.h"
#include "STM32G0_Pins_config.h"

#define CANtoCAN

extern TIM_HandleTypeDef htim2;

extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;

class HardwareDefinitions
{

private:

UART_HandleTypeDef huart1;

HardwareHandles hwHandles = 
{
    .can = &hfdcan1,
    .timer = &htim2,
    .uart = &huart1,
    .canInitFunc = MX_FDCAN1_Init
};


public:
const HardwareHandles* GetHardwareHandles();


    static void MX_CAN_Init(uint16_t baud);
    static void MX_FDCAN1_Init(uint16_t baud);
    static void MX_FDCAN2_Init(uint16_t baud);


/**
 * @brief Register multiple extended ID filters for FDCAN on STM32G0.
 * @param hfdcan      Pointer to your FDCAN handle (e.g., &hfdcan1)
 * @param ext_ids     Array of 29-bit extended CAN IDs
 * @param num_ids     Number of IDs in the array
 * @param fifo_num    0 for RXFIFO0, 1 for RXFIFO1
 * @return            HAL status
 *
 *
 */
// HAL_StatusTypeDef Register_FDCAN_ExtendedID_Filters(FDCAN_HandleTypeDef *hfdcan,
//                                                     const uint32_t *ext_ids,
//                                                     uint32_t num_ids,
//                                                     uint32_t fifo_num);




};









#endif // HARDWARE_DEFINITIONS_H




