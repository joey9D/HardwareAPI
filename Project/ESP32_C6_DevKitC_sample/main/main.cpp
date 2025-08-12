extern "C"
{
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
}

#include "hw_enum_classes.hpp"
#include "gpio.hpp"
#include "pin_config.hpp"

extern "C" void app_main(void)
{
    printf("Hello world!\n");

    for (auto pin : boardPins.allPins)
    {
        pin->gpio_init();
    }

    bool lastButtonState = boardPins.button.isDebouncePinOn();
    bool led_state = false;

    while (1)
    {
        bool currentButtonState = boardPins.button.isDebouncePinOn();

        if (!lastButtonState && currentButtonState)
        {
            led_state = !led_state;
            // gpio_set_level((gpio_num_t)boardPins.led.getPin(), led_state);
            boardPins.led.writePin(led_state);
        }
        lastButtonState = currentButtonState;
        vTaskDelay(pdMS_TO_TICKS(10)); // CPU entlasten
    }
    fflush(stdout);
    // esp_restart();
}