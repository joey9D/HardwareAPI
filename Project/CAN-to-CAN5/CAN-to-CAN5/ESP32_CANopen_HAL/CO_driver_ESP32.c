#include "CO_driver_ESP32.h"
#include "esp_log.h"

static const char *TAG = "CO_driver";

static QueueHandle_t rxQueue;

esp_err_t CO_CANinit(uint32_t baudRate) {
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CO_CAN_TX_PIN, CO_CAN_RX_PIN, TWAI_MODE_NORMAL);

    twai_timing_config_t t_config;
    switch (baudRate) {
        case 125000: t_config = TWAI_TIMING_CONFIG_125KBITS(); break;
        case 250000: t_config = TWAI_TIMING_CONFIG_250KBITS(); break;
        case 500000: t_config = TWAI_TIMING_CONFIG_500KBITS(); break;
        default:
            ESP_LOGE(TAG, "Unsupported baudrate: %u", baudRate);
            return ESP_ERR_INVALID_ARG;
    }

    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
    ESP_ERROR_CHECK(twai_start());

    rxQueue = xQueueCreate(16, sizeof(twai_message_t));
    ESP_LOGI(TAG, "CAN initialized at %u bps", baudRate);
    return ESP_OK;
}

esp_err_t CO_CANsend(const twai_message_t *msg) {
    return twai_transmit(msg, pdMS_TO_TICKS(100));
}

esp_err_t CO_CANread(twai_message_t *msg) {
    return twai_receive(msg, pdMS_TO_TICKS(10));
}

void CO_CANclose() {
    twai_stop();
    twai_driver_uninstall();
    vQueueDelete(rxQueue);
    ESP_LOGI(TAG, "CAN interface closed");
}

bool CO_CANisBusOff() {
    twai_status_info_t status;
    twai_get_status_info(&status);
    return status.state == TWAI_STATE_BUS_OFF;
}

bool CO_CANisRxPending() {
    twai_status_info_t status;
    twai_get_status_info(&status);
    return status.msgs_to_rx > 0;
}

bool CO_CANisTxBusy() {
    twai_status_info_t status;
    twai_get_status_info(&status);
    return status.tx_buffer_state == TWAI_BUFFER_FULL;
}
