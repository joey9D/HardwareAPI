//#ifdef __cplusplus
//#include <cassert>
//#else
#include <assert.h>
//#endif

#include "stm32_gpio.h"
#include "stm32x0_gpio_mapping.hpp"



//using namespace stm32;

stm32::Gpio::Gpio(
	uint16_t pin,
	Port port,
	Mode mode,
	Pull pull,
	Speed speed)
	: _pin(pin), _port(port), _mode(mode), _pull(pull), _speed(speed)
{
	assert(stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(port)]);
	assert(stm32::Gpio::_pin < stm32x0_gpio_mapping::pin_count);

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

// stm32::Gpio::~Gpio()
// {
// 	// default destructor
// }

[[nodiscard]] uint16_t stm32::Gpio::getPin() const {    return _pin;    }
[[nodiscard]] stm32::Gpio::Port stm32::Gpio::getPort() const {    return _port;   }
[[nodiscard]] GPIO_TypeDef *stm32::Gpio::get_GPIO_TypeDef_port() const
{
	return stm32x0_gpio_mapping::gpio_port[static_cast<size_t>(stm32::Gpio::_port)];
}
[[nodiscard]] stm32::Gpio::Mode stm32::Gpio::getMode() const {    return _mode;   }
[[nodiscard]] stm32::Gpio::Pull stm32::Gpio::getPull() const {    return _pull;   }
[[nodiscard]] stm32::Gpio::Speed stm32::Gpio::getSpeed() const {    return _speed;   }


[[nodiscard]] bool stm32::Gpio::readPin() const
{
    return HAL_GPIO_ReadPin(get_GPIO_TypeDef_port(), getPin());
}

void stm32::Gpio::writePin(bool value)
{
    HAL_GPIO_WritePin(get_GPIO_TypeDef_port(), static_cast<uint16_t>(getPin()), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void stm32::Gpio::togglePin() const
{
    HAL_GPIO_TogglePin(get_GPIO_TypeDef_port(), static_cast<uint16_t>(getPin()));
}

bool stm32::Gpio::lockPin() const
{
    return static_cast<bool>(HAL_GPIO_LockPin(get_GPIO_TypeDef_port(), static_cast<uint16_t>(getPin())));
};
