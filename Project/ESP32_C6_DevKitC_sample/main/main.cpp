extern "C" {
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
}


class DebounceButton {
public:
    DebounceButton(int pin, int64_t debounceTimeUs)
        : _pin(pin), _debounceTime(debounceTimeUs), _debounceState(0) {
        _lastTimeUs = 0;
    }

    bool isDebouncePinOn() {
        bool retval = false;
        int level = gpio_get_level((gpio_num_t)_pin);

        switch (_debounceState) {
        case 0: // pin off idle
            if (level == 0) { // gedrückt (Pull-Up)
                _lastTimeUs = esp_timer_get_time();
                _debounceState = 1;
            }
            break;
        case 1: // pin off debounce
            if (level == 0) {
                if ((esp_timer_get_time() - _lastTimeUs) > _debounceTime) {
                    _debounceState = 2;
                }
            } else {
                _debounceState = 0;
            }
            break;
        case 2: // pin on idle
            retval = true;
            if (level != 0) {
                _lastTimeUs = esp_timer_get_time();
                _debounceState = 3;
            }
            break;
        case 3: // pin on debounce
            retval = true;
            if (level != 0) {
                if ((esp_timer_get_time() - _lastTimeUs) > _debounceTime) {
                    _debounceState = 0;
                }
            } else {
                _debounceState = 2;
            }
            break;
        default:
            _debounceState = 0;
            break;
        }
        return retval;
    }

private:
    int _pin;
    int64_t _debounceTime;
    int _debounceState;
    int64_t _lastTimeUs;
};

extern "C" void app_main(void)
{
    printf("Hello world!\n");

    int led_pin = 15;
    int button_pin = 9;

    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << led_pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << button_pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&led_config);
    gpio_config(&button_config);

    DebounceButton button(button_pin, 50000); // 50ms debounce

    bool lastButtonState = button.isDebouncePinOn();
    bool led_state = false;

    while (1) {
        bool currentButtonState = button.isDebouncePinOn();

        if (!lastButtonState && currentButtonState) {
            led_state = !led_state;
            gpio_set_level((gpio_num_t)led_pin, led_state);
        }
        lastButtonState = currentButtonState;
        vTaskDelay(pdMS_TO_TICKS(10)); // CPU entlasten
    }
    fflush(stdout);
    // esp_restart();
}