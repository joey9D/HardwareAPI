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

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    writePin();

    GPIO_InitStruct.Pin = _pin;
}

STM32Gpio::~STM32Gpio() = default;

uint16_t STM32Gpio::getPin() const {    return _pin;    }
GPIO_TypeDef* STM32Gpio::getPort() const
{
    return stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(_port)];
}
STM32Gpio::Mode STM32Gpio::getMode() const {    return _mode;   }
STM32Gpio::Pull STM32Gpio::getPull() const {    return _pull;   }
STM32Gpio::Speed STM32Gpio::getSpeed() const {    return _speed;   }

bool STM32Gpio::readPin() const
{
    return HAL_GPIO_ReadPin(getPort(), getPin());
}

void STM32Gpio::writePin(bool value) const
{
    HAL_GPIO_WritePin(getPort(), getPin(), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void STM32Gpio::togglePin() const
{
    HAL_GPIO_TogglePin(getPort(), getPin());
}
