#include "CO_storageBlank.h"
#include "esp_log.h"

static const char *TAG = "CO_storage";

void CO_storage_init() {
    ESP_LOGI(TAG, "Storage system initialized (blank stub)");
}

void CO_storage_save() {
    ESP_LOGI(TAG, "Pretend to save configuration");
}
