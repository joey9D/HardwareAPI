#ifndef CO_DRIVER_ESP32_H
#define CO_DRIVER_ESP32_H

#include "driver/twai.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "CO_driver_target.h"

#define CO_CAN_CLOCK 80000000U

esp_err_t CO_CANinit(uint32_t baudRate);
esp_err_t CO_CANsend(const twai_message_t *msg);
esp_err_t CO_CANread(twai_message_t *msg);
void CO_CANclose();
bool CO_CANisBusOff();
bool CO_CANisRxPending();
bool CO_CANisTxBusy();

#endif // CO_DRIVER_ESP32_H
