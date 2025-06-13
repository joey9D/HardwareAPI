#include <cassert>
#include "stm32_gpio.hpp"
#include "stm32_gpio_mapping.hpp"

STM32Gpio::STM32Gpio(
    uint16_t pin,
    Port port,
    Mode mode,
    Pull pull,
    Speed speed)
    : _pin(pin), _port(port), _mode(mode), _pull(pull), _speed(speed)
{
    assert(pin < stm32x0_gpio_mapping::pin_count);
    assert(port < stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(port)]);


}
