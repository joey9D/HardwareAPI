#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

void app_main(void)
{

    const gpio_num_t BUTTON_GPIO = GPIO_NUM_9; // Beispiel: Boot-Button
    const gpio_num_t LED_GPIO = GPIO_NUM_15;   // Beispiel: Onboard-LED

    // GPIO initialisieren
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << BUTTON_GPIO);
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED_GPIO);
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    bool lastButtonState = gpio_get_level(BUTTON_GPIO);
    bool led_state = false;

    while (1)
    {
        bool currentButtonState = gpio_get_level(BUTTON_GPIO);

        // Toggle LED on button press (rising edge detection)
        if (!lastButtonState && currentButtonState)
        {
            led_state = !led_state;
            gpio_set_level(LED_GPIO, led_state);
        }

        lastButtonState = currentButtonState;

        vTaskDelay(pdMS_TO_TICKS(10)); // 10ms delay

        ESP_LOGI("example", "LED State: %s", led_state ? "ON" : "OFF");
    }
}
