extern "C" {
#include <stdio.h>

#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_timer.h"

}


extern "C"{

    void toggle_led(bool led_state, int pin)
    {
        gpio_num_t gpio_pin = static_cast<gpio_num_t>(pin);
        if (led_state)
            gpio_set_level(gpio_pin, !led_state);
        else
            gpio_set_level(gpio_pin, led_state);
    }

    bool is_button_pressed(int pin)
    {
        gpio_num_t gpio_pin = static_cast<gpio_num_t>(pin);
        static int64_t last_time_us = 0;
        const int64_t debounce_us = 50000; // 50 ms

        int level = gpio_get_level(gpio_pin);
        if (level == 0)  // gedrückt (da Pull-Up aktiviert)
        {
            int64_t now = esp_timer_get_time();
            if ((now - last_time_us) > debounce_us)
            {
                last_time_us = now;
                return true;
            }
        }
        return false;
    }
    
    void app_main(void)
    {
        printf("Hello world!\n");

        int led_pin = 15;
        int button_pin = 9;

        gpio_config_t led_config =
        {
            .pin_bit_mask = (1ULL << led_pin), // Pin 15
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };

        gpio_config_t button_config =
        {
            .pin_bit_mask = (1ULL << button_pin), // Pin 9
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };

        gpio_config(&led_config);
        gpio_config(&button_config);

        bool lastButtonState = false;
        bool led_state = false;

        while(1) 
        {
            bool currentButtonState = is_button_pressed(button_pin);
            if (!lastButtonState && currentButtonState) 
            {  
                toggle_led(led_state, led_pin);
            }
            lastButtonState = currentButtonState;
            vTaskDelay(pdMS_TO_TICKS(10)); // CPU entlasten

        }
    // for (int i = 10; i >= 0; i--) {
    //     printf("Restarting in %d seconds...\n", i);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
    fflush(stdout);
    // esp_restart();
}

} /* extern C */