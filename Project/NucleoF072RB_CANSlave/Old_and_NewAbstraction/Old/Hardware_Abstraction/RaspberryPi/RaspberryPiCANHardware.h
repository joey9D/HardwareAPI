#ifndef RASPBERRY_PI_CAN_HARDWARE_H
#define RASPBERRY_PI_CAN_HARDWARE_H

#include "CANHardwareInterface.h"
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <unistd.h>

class RaspberryPiCANHardware : public CANHardwareInterface {
private:
    int socket_fd;

public:
    RaspberryPiCANHardware();
    ~RaspberryPiCANHardware();
    void CAN_Init() override;
    void CAN_Start() override;
    void CAN_Transmit(const char* data, int length) override;
    void CAN_Receive(char* buffer, int length) override;
    void GPIO_Read(int pin) override;
    void GPIO_Write(int pin, bool value) override;
    unsigned long GetTick() override;
};

#endif // RASPBERRY_PI_CAN_HARDWARE_H
