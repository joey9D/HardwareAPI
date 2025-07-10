#include "CO_app_ESP32.h"
#include "CO_driver_ESP32.h"
#include "esp_log.h"

static const char *TAG = "CO_app";

void CO_app_init() {
    ESP_LOGI(TAG, "Initializing CANopen application...");
    CO_CANinit(CO_CAN_BITRATE);
}

void CO_app_process() {
    twai_message_t msg;
    if (CO_CANisRxPending() && CO_CANread(&msg) == ESP_OK) {
        ESP_LOGI(TAG, "Received ID: 0x%X, DLC: %d", msg.identifier, msg.data_length_code);
    }

    twai_message_t txMsg = {
        .identifier = 0x123,
        .data_length_code = 2,
        .data = {0xDE, 0xAD},
        .flags = 0
    };
    CO_CANsend(&txMsg);
    vTaskDelay(pdMS_TO_TICKS(1000));
}

void CO_app_shutdown() {
    CO_CANclose();
    ESP_LOGI(TAG, "CANopen application shut down");
}
