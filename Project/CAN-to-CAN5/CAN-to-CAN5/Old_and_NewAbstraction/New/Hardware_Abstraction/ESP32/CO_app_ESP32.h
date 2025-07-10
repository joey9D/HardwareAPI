#ifndef CO_APP_ESP32_H
#define CO_APP_ESP32_H

#include "CO_driver_ESP32.h"

typedef struct {
    uint8_t desiredNodeID;
    uint8_t activeNodeID;
    uint32_t baudrate;
    CO_CANmodule_ESP32* can_hw;
    CO_t* canOpenStack;
} CANopenNodeESP32;

void canopen_app_init(CANopenNodeESP32* node);
uint8_t canopen_app_process(void);

#endif // CO_APP_ESP32_H
