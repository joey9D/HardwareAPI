#include <GPIObase.h>


GPIObase::GPIObase(uint32_t pin, uint32_t mode, bool pinInverted)
    : _pin(pin), _mode(mode), _pinInverted(pinInverted) 
{

}

GPIObase::~GPIObase() {}


uint32_t GPIObase::getPin() const {
    return _pin;
}

uint32_t GPIObase::getMode() const {
    return _mode;
}

bool GPIObase::isPinInverted() const {
    return _pinInverted;
}


