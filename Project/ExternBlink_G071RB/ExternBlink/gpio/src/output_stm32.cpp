/*
 * output_stm32.cpp
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */


#include "output_stm32.h"

Output_stm32::Output_stm32(uint32_t pin,
		uint32_t mode,
		uint32_t pull,
		uint32_t speed,
		uint32_t alternate,
		GPIO_TypeDef *port,
		bool pinInverted)
	: GPIO_stm32(pin, mode, pull, speed,  alternate, port, pinInverted)
{
	setPinOutput(false);
}


void Output_stm32::setPinOutput(bool activePinState)
{
    GPIO_PinState newPinState;
    _oldPinState = activePinState;

    if (isPinInverted()) {
        activePinState = !activePinState;
    }

    if (activePinState) {
        newPinState = GPIO_PIN_SET;
    } else {
        newPinState = GPIO_PIN_RESET;
    }

    HAL_GPIO_WritePin(getPort(), getPin(), newPinState);
}

void Output_stm32::toggle() {
    setPinOutput(!_oldPinState);
}
