 /*
 * adapter_stm32g071xx_gpio.cpp
 *
 *  Created on: Mar 5, 2025
 *      Author: jan.kristel
 */

#include <adapter_stm32_timer.hpp>
#include "adapter_stm32_gpio.hpp"

AdapterSTM32GPIO :: AdapterSTM32GPIO(
		uint16_t pin, int mode, int pull, int speed, GPIO_TypeDef* port,
		bool invertedPin = false) : AdapterBaseGPIO(pin, mode, invertedPin) {
	_pull = pull;
	_speed = speed;
	_port = port;
	write(false);
}

AdapterSTM32GPIO :: ~AdapterSTM32GPIO() {};

/**
 * @brief getter
 */
uint16_t AdapterSTM32GPIO :: getPin() const {
	return _pin;
}

int AdapterSTM32GPIO :: getPull() const {
	return _pull;
}

int AdapterSTM32GPIO :: getSpeed() const {
	return _speed;
}

bool AdapterSTM32GPIO :: isPinOn() const {
	return _pinState;
}

GPIO_TypeDef* AdapterSTM32GPIO :: getPort() const {
	return _port;
}

bool AdapterSTM32GPIO :: isPinInverted() const {
	return _invertedPin;
}


/**
 * @brief Methods
 */
void AdapterSTM32GPIO :: config() {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = _pin;
	GPIO_InitStruct.Mode = static_cast<uint32_t>(_mode);
	GPIO_InitStruct.Pull = static_cast<uint32_t>(_pull);
	GPIO_InitStruct.Speed = static_cast<uint32_t>(_speed);
	HAL_GPIO_Init(_port, &GPIO_InitStruct);
} /* END CONFIG */

void AdapterSTM32GPIO :: write(bool onState) {
	if (_oldState != onState) {
		GPIO_PinState PinState;
		/**
		 * With _oldState always on 'true', calling write with 'false' inside the constructor,
		 * sets the output-pin always to 'false', therefore turning it off.
		 */
		_oldState = onState;

		if (isPinInverted()) {
			onState = !onState;
		}

		if (onState) {
			PinState = GPIO_PIN_SET;
		} else {
			PinState = GPIO_PIN_RESET;
		}

		HAL_GPIO_WritePin(getPort(), getPin(), PinState);
	}
} /* END WRITE*/

bool AdapterSTM32GPIO :: read() const {
	bool retvalue = false;

	if (HAL_GPIO_ReadPin(getPort(), getPin()) == GPIO_PIN_SET) {
		retvalue = true;
	} else {
		retvalue = false;
	}

	if (isPinInverted) {
		retvalue = !retvalue;
	}

	return retvalue;
} /* END READ */

void AdapterSTM32GPIO :: toggle(uint16_t pin) {
	HAL_GPIO_TogglePin(_port, pin);
} /* END TOPGGLE */



















