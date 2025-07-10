#ifndef ZEPHYR_CAN_HARDWARE_H
#define ZEPHYR_CAN_HARDWARE_H

#include "CANHardwareInterface.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>

class ZephyrCANHardware : public CANHardwareInterface {
private:
    const struct device* can_dev;

public:
    ZephyrCANHardware();  // Constructor

    void CAN_Init() override;
    void CAN_Start() override;
    void CAN_Transmit(const char* data, int length) override;
    void CAN_Receive(char* buffer, int length) override;
    void GPIO_Read(int pin) override;
    void GPIO_Write(int pin, bool value) override;
    unsigned long GetTick() override;
};

#endif // ZEPHYR_CAN_HARDWARE_H
