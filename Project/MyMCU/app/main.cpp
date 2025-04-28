#include "main.h"

int main()
{
    periph::systick::init();

    periph::gpio_stm32c0 led(periph::gpio_stm32c0::port::a, 9, periph::gpio::mode::digital_output);

    while(1)
    {
        led.toggle();
        // TODO: implement delay function to avoid using FreeRTOS task/delay etc..
        // delay(1000);
    }

    return 0;
}
