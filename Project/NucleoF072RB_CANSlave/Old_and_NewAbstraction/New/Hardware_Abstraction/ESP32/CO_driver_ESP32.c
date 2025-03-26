#include "CO_driver_ESP32.h"
#include "CANopen.h"

static CO_CANmodule_t* CANModule_local = NULL;

void CO_CANsetConfigurationMode(void* CANptr) {
    twai_stop();
}

void CO_CANsetNormalMode(CO_CANmodule_t* CANmodule) {
    twai_start();
    CANmodule->CANnormal = true;
}

CO_ReturnError_t CO_CANmodule_init(CO_CANmodule_t* CANmodule, void* CANptr, ...) {
    CO_CANmodule_ESP32* esp_can = (CO_CANmodule_ESP32*)CANptr;
    
    // Initialize TWAI
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_21, GPIO_NUM_22, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_250KBITS();
    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, NULL));
    
    CANmodule->CANptr = CANptr;
    esp_can->can_mutex = xSemaphoreCreateMutex();
    return CO_ERROR_NO;
}

CO_ReturnError_t CO_CANsend(CO_CANmodule_t* CANmodule, CO_CANtx_t* buffer) {
    twai_message_t msg = {
        .identifier = buffer->ident & 0x7FF,
        .data_length_code = buffer->DLC,
        .flags = (buffer->ident & FLAG_RTR) ? TWAI_MSG_FLAG_RTR : 0
    };
    memcpy(msg.data, buffer->data, buffer->DLC);
    return (twai_transmit(&msg, pdMS_TO_TICKS(100)) == ESP_OK) ? CO_ERROR_NO : CO_ERROR_TX_OVERFLOW;
}
