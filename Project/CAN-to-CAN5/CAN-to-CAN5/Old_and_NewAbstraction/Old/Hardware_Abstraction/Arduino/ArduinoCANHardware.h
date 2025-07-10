#ifndef ARDUINO_CAN_HARDWARE_H
#define ARDUINO_CAN_HARDWARE_H

#include "../CANHardwareInterface.h"
#include <CAN.h> // Arduino CAN library

class ArduinoCANHardware : public CANHardwareInterface {
public:
    void CAN_Init() override;
    void CAN_Start() override;
    void CAN_Transmit(const char* data, int length) override;
    void CAN_Receive(char* buffer, int length) override;
    void GPIO_Read(int pin) override;
    void GPIO_Write(int pin, bool value) override;
    unsigned long GetTick() override;
};

#endif // ARDUINO_CAN_HARDWARE_H
