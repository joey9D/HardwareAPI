#include "OutputArduino.h"

OutputArduino::OutputArduino(uint8_t pin, uint8_t mode, bool pinInverted) 
    : GPIOarduino(pin, mode, pinInverted)
{
    setPinOutput(false);
}

bool OutputArduino::isOutputPinOn() const {
    return _oldPinState;
}


void OutputArduino::setPinOutput(bool activePinState)
{
    PinStatus newPinState;
    _oldPinState = activePinState;

    if (isPinInverted()) {
        activePinState = !activePinState;
    }

    if (activePinState) {
        newPinState = HIGH;
    } else {
        newPinState = LOW;
    }

    digitalWrite(getPin(), newPinState);
}

void OutputArduino::toggle() {
    setPinOutput(!_oldPinState);
}