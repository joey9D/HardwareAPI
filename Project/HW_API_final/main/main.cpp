#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// HW_API includes (ChatGPT Empfehlung: Verwende die ursprüngliche HW_API)
#include "hw_factory.hpp"
#include "hw_interface.hpp"

static const char *TAG = "HW_API_ESP32";

// ESP-IDF Main-Funktion (statt main())
extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "Starting HW_API ESP32 Application");
    ESP_LOGI(TAG, "ChatGPT ESP-IDF Integration successful!");
    
    try {
        // Erstelle Hardware Interface über Factory
        auto hw = HardwareFactory::create();
        
        if (hw) {
            ESP_LOGI(TAG, "Hardware interface created successfully");
            
            // Test GPIO (wenn verfügbar)
            // hw->gpio_test();
            
        } else {
            ESP_LOGE(TAG, "Failed to create hardware interface");
        }
        
    } catch (const std::exception& e) {
        ESP_LOGE(TAG, "Exception: %s", e.what());
    }
    
    ESP_LOGI(TAG, "Application initialized, running main loop...");
    
    // Haupt-Task-Schleife
    while (1) {
        ESP_LOGI(TAG, "HW_API ESP32 running...");
        vTaskDelay(pdMS_TO_TICKS(5000)); // 5 Sekunden warten
    }
}
