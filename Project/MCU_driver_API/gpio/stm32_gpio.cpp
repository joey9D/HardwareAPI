#include "stm32_gpio.hpp"
#include "stm32_gpio_mapping.hpp"
#include "stm32c0xx_hal_gpio.h"


STM32Gpio::STM32Gpio(
    uint16_t pin,
    Port port,
    Mode mode,
    Pull pull,
    Speed speed)
    : _pin(pin), _port(port), _mode(mode), _pull(pull), _speed(speed)
{
    assert(stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(port)]);
    assert(pin < stm32x0_gpio_mapping::pin_count);

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    clock_enable(_port);

    writePin(0);

    GPIO_InitStruct.Pin = static_cast<uint32_t>(_pin);
    GPIO_InitStruct.Mode = static_cast<uint32_t>(_mode);
    GPIO_InitStruct.Pull = static_cast<uint32_t>(_pull);
    GPIO_InitStruct.Speed = static_cast<uint32_t>(_speed);
    HAL_GPIO_Init(getPort(), &GPIO_InitStruct);
}

STM32Gpio::~STM32Gpio()
{

};

// getter
[[nodiscard]] uint16_t STM32Gpio::getPin() const final {    return _pin;    }
[[nodiscard]] Port STM32Gpio::getPort() const final
{
    return stm32x0_gpio_mapping::gpio_port[static_cast<size_t>(_port)];
}
[[nodiscard]] Mode STM32Gpio::getMode() const final {    return _mode;   }
[[nodiscard]] Pull STM32Gpio::getPull() const final {    return _pull;   }
[[nodiscard]] Speed STM32Gpio::getSpeed() const final {    return _speed;   }


// gpio function abstraction for hal functions
[[nodiscard]] bool STM32Gpio::readPin() const final
{
    return HAL_GPIO_ReadPin(getPort(), getPin());
}

void STM32Gpio::writePin(bool value) final
{
    HAL_GPIO_WritePin(getPort(), static_cast<uint16_t>(getPin()), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void STM32Gpio::togglePin() final
{
    HAL_GPIO_TogglePin(getPort(), static_cast<uint16_t>(getPin()));
}

bool STM32Gpio::lockPin() final
{
    return static_cast<bool>(HAL_GPIO_LockPin(getPort(), static_cast<uint16_t>(getPin())));
}

// void EXTI_IRQHandler() final
// {
//     HAL_GPIO_EXTI_IRQHandler(getPin());
// }

// void EXTI_Rising_Callback() final
// {
//     HAL_GPIO_EXTI_Rising_Callback(getPin());
// }

// void EXTI_Falling_Callback() final
// {
//     HAL_GPIO_EXTI_Falling_Callback(getPin());
// }
