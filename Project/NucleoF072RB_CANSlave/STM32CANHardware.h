#ifndef STM32_CAN_HARDWARE_H
#define STM32_CAN_HARDWARE_H


#include "../CANHardwareInterface.h"



// Include C headers like STM32 HAL
#include "../../Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal.h"


// Declare external hardware object


#ifdef __cplusplus
class STM32CANHardware : public CANHardwareInterface
{
public:
   // void CAN_Init() override;
   // void CAN_Start() override;
   // void CAN_Transmit(const char* data, int length) override;
  // void CAN_Receive(char* buffer, int length) override;
    bool GPIO_Read(int pin) override;
    void GPIO_Write(int pin, bool value) override;
    unsigned long GetTick() override;
    ~STM32CANHardware() override = default;
};


#endif

#endif // STM32_CAN_HARDWARE_H
