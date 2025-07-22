/*
 * gpio.cpp
 *
 *  Created on: Jul 11, 2025
 *      Author: jan.kristel
 */
#include <cassert>
#include <type_traits>

#include "stm32c0xx_hal.h"

#include "gpio.hpp"
#include "hw_factory.hpp"
#include "hw_enum_classes.hpp"
#include "stm32x0_gpio_mapping.hpp"

Gpio::Gpio(	uint16_t pin,
	Port port,
	Mode mode,
	Pull pull,
	Speed speed,
	bool inverted,
	uint32_t debounceTime,
	uint8_t debounceState,
	ExtiTrigger extiTrigger
) : _pin(pin), _port(port), _mode(mode), _pull(pull), _speed(speed), _inverted(inverted), _debounceTime(debounceTime), _debounceState(debounceState), _extiTrigger(extiTrigger)
{}

void Gpio::gpio_init()
{
	assert(stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(_port)]);
	assert(_pin < stm32x0_gpio_mapping::pin_count);


	GPIO_InitTypeDef GPIO_InitStruct = {0};
	port_clock_enable(_port);

	uint16_t pin_msk = (1UL << _pin);

	if (_mode == Mode::Output_Push_Pull || _mode == Mode::Output_Open_Drain)
	{
		HAL_GPIO_WritePin(get_GPIO_TypeDef_port(), pin_msk, GPIO_PIN_RESET);
	}

	GPIO_InitStruct.Pin = pin_msk;
	GPIO_InitStruct.Mode = static_cast<uint32_t>(_mode);
	GPIO_InitStruct.Pull = static_cast<uint32_t>(_pull);
	GPIO_InitStruct.Speed = static_cast<uint32_t>(_speed);

	if (_extiTrigger != ExtiTrigger::None)
	{
		switch(_extiTrigger)
		{
			case ExtiTrigger::Rising:
				GPIO_InitStruct.Mode = Mode::Interrupt_Rising;
				break;
			case ExtiTrigger::Falling:
				GPIO_InitStruct.Mode = Mode::Interrupt_Falling;
				break;
			case ExtiTrigger::Rising_Falling:
				GPIO_InitStruct.Mode = Mode::Interrupt_Rising_Falling;
				break;
			default:
				// GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // Default to input if no trigger is set
				break;
		}
	}

	HAL_GPIO_Init(get_GPIO_TypeDef_port(),&GPIO_InitStruct);
}


/**
 * @brief using functions
 */

bool Gpio::readPin() const
{
	 return HAL_GPIO_ReadPin(get_GPIO_TypeDef_port(), getPin());
}

void Gpio::writePin(bool value) const
{
    HAL_GPIO_WritePin(get_GPIO_TypeDef_port(), static_cast<uint16_t>(getPin()), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Gpio::togglePin() const
{
    HAL_GPIO_TogglePin(get_GPIO_TypeDef_port(), static_cast<uint16_t>(getPin()));
}

/**
 * @brief Helper functions
 */
void Gpio::port_clock_enable(Port port) const
{
	switch (port)
	{
		case Port::A: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
		case Port::B: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
		case Port::C: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
		case Port::D: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
//	            case Port::E: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
		case Port::F: __HAL_RCC_GPIOF_CLK_ENABLE(); break;
	}
}

bool Gpio::isPinOn() const
{
	bool retval = false;

	/**
	 * @note eihter like this or using readPin(),
	 * so that for future adjustments/portability you can just copy this whole function
	 */
	if (HAL_GPIO_ReadPin(get_GPIO_TypeDef_port(), getPin()) == GPIO_PIN_SET)
	{
		retval = true;
	}

	if (isPinInverted())
	{
		retval = !retval;
	}

	return retval;
}

bool Gpio::isDebouncePinOn()
{
	bool retval = false;

	if (_debounceTime != 0)
	{
		switch (_debounceState)
		{
		case 0://pin off idle
			if(isPinOn())
			{
				_debounceTimer.startTime(_debounceTime);
				_debounceState = 1;//pin off debounce
			}
			break;
		case 1://pin off debounce
			if(isPinOn())
			{
				if(_debounceTimer.isTimeExpired())
				{
					_debounceState = 2;
				}
			}
			else
			{
				_debounceTimer.stopTime();
				_debounceState = 0;//pin off idle
			}
			break;
		case 2://pin on idle
			retval = true;
			if(!isPinOn())
			{
				_debounceTimer.startTime(_debounceTime);
				_debounceState = 3;//pin on debounce
			}
			break;
		case 3://pin on debounce
			retval = true;
			if(!isPinOn())
			{
				if(_debounceTimer.isTimeExpired())
				{
					_debounceState = 0;//pin off idle
				}
			}
			else
			{
				_debounceTimer.stopTime();
				_debounceState = 2;//pin on idle
			}
			break;
		default:
			_debounceState = 0;
			break;
		}
	}
	else
	{
		retval = true;
	}

	return retval;
}

bool Gpio::isPinInverted() const
{
	return _inverted;
}




/**
 * @brief Getter funcitons
 */
uint16_t Gpio::getPin() const { return (1 << _pin); }

GPIO_TypeDef *Gpio::get_GPIO_TypeDef_port() const
{
	using PortIndex = std::underlying_type_t<decltype(_port)>;
	return stm32x0_gpio_mapping::gpio_port[static_cast<PortIndex>(_port)];
}

Mode Gpio::getMode() const { return _mode; }

Pull Gpio::getPull() const { return _pull; }

Speed Gpio::getSpeed() const { return _speed; }
