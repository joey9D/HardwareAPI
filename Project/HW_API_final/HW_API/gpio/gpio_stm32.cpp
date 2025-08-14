/*
 * gpio.cpp
 *
 *  Created on: Jul 11, 2025
 *      Author: jan.kristel
 */
#include <gpio_stm32.hpp>
#include <cassert>
#include <type_traits>

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"

#include "hw_factory.hpp"
#include "hw_enum_classes.hpp"
#include "stm32x0_gpio_mapping.hpp"

// Mapping functions to convert enum classes to HAL constants
namespace
{
	uint32_t modeToHAL(Mode mode)
	{
		switch (mode)
		{
		case Mode::Input:
			return GPIO_MODE_INPUT;
		case Mode::Output_Push_Pull:
			return GPIO_MODE_OUTPUT_PP;
		case Mode::Output_Open_Drain:
			return GPIO_MODE_OUTPUT_OD;
		case Mode::Alternate_Push_Pull:
			return GPIO_MODE_AF_PP;
		case Mode::Alternate_Open_Drain:
			return GPIO_MODE_AF_OD;
		case Mode::Analog:
			return GPIO_MODE_ANALOG;
		case Mode::Interrupt_Rising:
			return GPIO_MODE_IT_RISING;
		case Mode::Interrupt_Falling:
			return GPIO_MODE_IT_FALLING;
		case Mode::Interrupt_RisingFalling:
			return GPIO_MODE_IT_RISING_FALLING;
		case Mode::Event_Rising:
			return GPIO_MODE_EVT_RISING;
		case Mode::Event_Falling:
			return GPIO_MODE_EVT_FALLING;
		case Mode::Event_RisingFalling:
			return GPIO_MODE_EVT_RISING_FALLING;
		default:
			return GPIO_MODE_INPUT;
		}
	}

	uint32_t pullToHAL(Pull pull)
	{
		switch (pull)
		{
		case Pull::None:
			return GPIO_NOPULL;
		case Pull::Up:
			return GPIO_PULLUP;
		case Pull::Down:
			return GPIO_PULLDOWN;
		default:
			return GPIO_NOPULL;
		}
	}

	uint32_t speedToHAL(Speed speed)
	{
		switch (speed)
		{
		case Speed::Low:
			return GPIO_SPEED_FREQ_LOW;
		case Speed::Medium:
			return GPIO_SPEED_FREQ_MEDIUM;
		case Speed::High:
			return GPIO_SPEED_FREQ_HIGH;
#ifdef GPIO_SPEED_FREQ_VERY_HIGH // Nicht alle STM32 haben Very_High
		case Speed::Very_High:
			return GPIO_SPEED_FREQ_VERY_HIGH;
#else
		case Speed::Very_High:
			return GPIO_SPEED_FREQ_HIGH; // Fallback für ältere STM32
#endif
		default:
			return GPIO_SPEED_FREQ_LOW;
		}
	}

	uint32_t alternateToHAL(Alternate alternate)
	{
		if (alternate == Alternate::None)
		{
			return 0; // Kein Alternate Function
		}
		return static_cast<uint32_t>(alternate);
	}
}

Gpio::Gpio(
	uint16_t pin,
	Port port,
	Mode mode,
	Pull pull,
	Speed speed,
	Alternate alternate,
	bool inverted,
	uint32_t debounceTime,
	uint8_t debounceState,
	ExtiTrigger extiTrigger) : _pin(pin), _port(port), _mode(mode), _pull(pull), _speed(speed), _alternate(alternate), _inverted(inverted), _debounceTime(debounceTime), _debounceState(debounceState), _extiTrigger(extiTrigger)
{
}

void Gpio::gpio_init()
{
	assert(stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(_port)]);
	assert(_pin < stm32x0_gpio_mapping::pin_count);

	// Explicit initialization to avoid memset debugging interference (C++17 compliant)
	GPIO_InitTypeDef GPIO_InitStruct{};
	port_clock_enable(_port);

	uint16_t pin_msk = (1UL << _pin);

	if (_mode == Mode::Output_Push_Pull || _mode == Mode::Output_Open_Drain)
	{
		HAL_GPIO_WritePin(get_GPIO_TypeDef_port(), pin_msk, GPIO_PIN_RESET);
	}

	GPIO_InitStruct.Pin = pin_msk;
	GPIO_InitStruct.Mode = modeToHAL(_mode);
	GPIO_InitStruct.Pull = pullToHAL(_pull);
	GPIO_InitStruct.Speed = speedToHAL(_speed);

	// Alternate Function
	if (_alternate != Alternate::None &&
		(_mode == Mode::Alternate_Push_Pull || _mode == Mode::Alternate_Open_Drain))
	{
		GPIO_InitStruct.Alternate = alternateToHAL(_alternate);
	}

	HAL_GPIO_Init(get_GPIO_TypeDef_port(), &GPIO_InitStruct);
}

/**
 * @brief using functions
 */

[[nodiscard]] bool Gpio::readPin() const
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
 * brief Helper functions
 */
void Gpio::port_clock_enable(Port port) const
{
	switch (port)
	{
	case Port::A:
		__HAL_RCC_GPIOA_CLK_ENABLE();
		break;
	case Port::B:
		__HAL_RCC_GPIOB_CLK_ENABLE();
		break;
	case Port::C:
		__HAL_RCC_GPIOC_CLK_ENABLE();
		break;
	case Port::D:
		__HAL_RCC_GPIOD_CLK_ENABLE();
		break;
#ifdef __HAL_RCC_GPIOE_CLK_ENABLE // Nicht alle STM32 haben Port E
	case Port::E:
		__HAL_RCC_GPIOE_CLK_ENABLE();
		break;
#endif
	case Port::F:
		__HAL_RCC_GPIOF_CLK_ENABLE();
		break;
#ifdef __HAL_RCC_GPIOG_CLK_ENABLE // Nur größere STM32 haben Port G,H,I
	case Port::G:
		__HAL_RCC_GPIOG_CLK_ENABLE();
		break;
#endif
#ifdef __HAL_RCC_GPIOH_CLK_ENABLE
	case Port::H:
		__HAL_RCC_GPIOH_CLK_ENABLE();
		break;
#endif
#ifdef __HAL_RCC_GPIOI_CLK_ENABLE
	case Port::I:
		__HAL_RCC_GPIOI_CLK_ENABLE();
		break;
#endif
	default:
		break; // Unbekannter Port
	}
}

[[nodiscard]] bool Gpio::isPinOn() const
{
	bool retval = false;

	/**
	 * @note either like this or using readPin(),
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

[[nodiscard]] bool Gpio::isDebouncePinOn()
{
	bool retval = false;

	if (_debounceTime != 0)
	{
		switch (_debounceState)
		{
		case 0: // pin off idle
			if (isPinOn())
			{
				debounceTimer.startTime(_debounceTime);
				_debounceState = 1; // pin off debounce
			}
			break;
		case 1: // pin off debounce
			if (isPinOn())
			{
				if (debounceTimer.isTimeExpired())
				{
					_debounceState = 2;
				}
			}
			else
			{
				debounceTimer.stopTime();
				_debounceState = 0; // pin off idle
			}
			break;
		case 2: // pin on idle
			retval = true;
			if (!isPinOn())
			{
				debounceTimer.startTime(_debounceTime);
				_debounceState = 3; // pin on debounce
			}
			break;
		case 3: // pin on debounce
			retval = true;
			if (!isPinOn())
			{
				if (debounceTimer.isTimeExpired())
				{
					_debounceState = 0; // pin off idle
				}
			}
			else
			{
				debounceTimer.stopTime();
				_debounceState = 2; // pin on idle
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

[[nodiscard]] bool Gpio::isPinInverted() const
{
	return _inverted;
}

/**
 * @brief Getter functions
 */
[[nodiscard]] uint16_t Gpio::getPin() const { return (1 << _pin); }

[[nodiscard]] GPIO_TypeDef *Gpio::get_GPIO_TypeDef_port() const
{
	using PortIndex = std::underlying_type_t<decltype(_port)>;
	return stm32x0_gpio_mapping::gpio_port[static_cast<PortIndex>(_port)];
}

[[nodiscard]] Mode Gpio::getMode() const { return _mode; }

[[nodiscard]] Pull Gpio::getPull() const { return _pull; }

[[nodiscard]] Speed Gpio::getSpeed() const { return _speed; }

[[nodiscard]] Alternate Gpio::getAlternate() const { return _alternate; }
