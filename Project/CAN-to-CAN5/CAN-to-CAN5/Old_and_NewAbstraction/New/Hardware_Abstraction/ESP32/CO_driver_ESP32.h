#ifndef CO_DRIVER_ESP32_H
#define CO_DRIVER_ESP32_H

#include "driver/twai.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#define CO_CONFIG_LSS (CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | CO_CONFIG_LSS_SLAVE)
#define CO_CONFIG_NMT (CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | CO_CONFIG_GLOBAL_FLAG_TIMERNEXT)
#define CO_CONFIG_SDO_SRV (CO_CONFIG_SDO_SRV_SEGMENTED | CO_CONFIG_FLAG_CALLBACK_PRE)

typedef struct {
    twai_general_config_t twai_config;
    twai_timing_config_t timing_config;
    uint32_t baudrate;
    SemaphoreHandle_t can_mutex;
} CO_CANmodule_ESP32;

// Locking Macros
#define CO_LOCK_CAN_SEND(CAN_MODULE) xSemaphoreTake((CAN_MODULE)->can_mutex, portMAX_DELAY)
#define CO_UNLOCK_CAN_SEND(CAN_MODULE) xSemaphoreGive((CAN_MODULE)->can_mutex)

#endif // CO_DRIVER_ESP32_H
