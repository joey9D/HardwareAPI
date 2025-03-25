#include "OutputSTM32.h"

OutputSTM32::OutputSTM32(uint32_t pin, uint32_t mode, GPIO_TypeDef *port, bool pinInverted)
    : GPIOstm32(pin, mode, port, pinInverted)
{
    setPinOutput(false);
}

bool OutputSTM32::isOutputPinOn() const {
    return _oldPinState;
}

void OutputSTM32::setPinOutput(bool activePinState)
{
    GPIO_PinState newPinState;
    _oldPinState = activePinState;

    if (isPinInverted()) {
        activePinState = !activePinState;
    }

    if (activePinState) {
        newPinState = HIGH;
    } else {
        newPinState = LOW;
    }

    HAL_GPIO_WritePin(getPort(), getPin(), newPinState);
}

void OutputSTM32::toggle() {
    setPinOutput(!_oldState);
}