//#ifdef __cplusplus
//#include <cassert>
//#else
#include <assert.h>
//#endif

#include "stm32_gpio.h"
#include "stm32x0_gpio_mapping.hpp"

#include "stm32c0xx_hal_gpio.h"

//using namespace stm32;

stm32::STM32Gpio::STM32Gpio(
	uint16_t pin,
	Port port,
	Mode mode,
	Pull pull,
	Speed speed)
	: _pin(pin), _port(port), _mode(mode), _pull(pull), _speed(speed)
{
	assert(stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(port)]);
	assert(stm32::STM32Gpio::_pin < stm32x0_gpio_mapping::pin_count);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	clock_enable(_port);

	writePin(0);

	GPIO_InitStruct.Pin = static_cast<uint32_t>(_pin);
	GPIO_InitStruct.Mode = static_cast<uint32_t>(_mode);
	GPIO_InitStruct.Pull = static_cast<uint32_t>(_pull);
	GPIO_InitStruct.Speed = static_cast<uint32_t>(_speed);
//	GPIO_TypeDef *typedef_port = getGPIOTypeDef();
	HAL_GPIO_Init(get_GPIO_TypeDef_port(),&GPIO_InitStruct);
}

stm32::STM32Gpio::~STM32Gpio()
{
	// default destructor
}

[[nodiscard]] uint16_t stm32::STM32Gpio::getPin() const {    return _pin;    }
[[nodiscard]] stm32::STM32Gpio::Port stm32::STM32Gpio::getPort() const {    return _port;   }
[[nodiscard]] GPIO_TypeDef *stm32::STM32Gpio::get_GPIO_TypeDef_port() const
{
	return stm32x0_gpio_mapping::gpio_port[static_cast<size_t>(stm32::STM32Gpio::_port)];
}
[[nodiscard]] stm32::STM32Gpio::Mode stm32::STM32Gpio::getMode() const {    return _mode;   }
[[nodiscard]] stm32::STM32Gpio::Pull stm32::STM32Gpio::getPull() const {    return _pull;   }
[[nodiscard]] stm32::STM32Gpio::Speed stm32::STM32Gpio::getSpeed() const {    return _speed;   }


[[nodiscard]] bool stm32::STM32Gpio::readPin() const final
{
    return HAL_GPIO_ReadPin(get_GPIO_TypeDef_port(), getPin());
}

void stm32::STM32Gpio::writePin(bool value) final
{
    HAL_GPIO_WritePin(get_GPIO_TypeDef_port(), static_cast<uint16_t>(getPin()), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void stm32::STM32Gpio::togglePin() final
{
    HAL_GPIO_TogglePin(get_GPIO_TypeDef_port(), static_cast<uint16_t>(getPin()));
}

bool stm32::STM32Gpio::lockPin() final
{
    return static_cast<bool>(HAL_GPIO_LockPin(get_GPIO_TypeDef_port(), static_cast<uint16_t>(getPin())));
};
