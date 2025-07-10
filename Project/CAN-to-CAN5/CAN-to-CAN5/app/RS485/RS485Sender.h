#pragma once
#include "RS485Protocol.h"

class RS485Sender {
public:
    static void init(void* uart, void* dePort, uint16_t dePin);
    static bool sendFrame(const RS485Frame& frame);
    static void sendPoll(uint8_t nodeId);
    static void sendLED(uint8_t nodeId, uint8_t action, uint8_t color, uint16_t delay_ms);
private:
    static void* _uart;
    static void* _dePort;
    static uint16_t _dePin;
    static void setTX(bool enable);
};
