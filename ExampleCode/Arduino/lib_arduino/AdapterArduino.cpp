#include <lib_arduino/AdapterArduino.h>

AdapterArduino::AdapterArduino(GPIObase *gpiobase)
    : _gpiobase(gpiobase)
{
    // empty
}

AdapterArduino::~AdapterArduino() {}

uint8_t AdapterArduino::getPin() const { 
    return static_cast<uint8_t>(_gpiobase->getPin());
}

uint8_t AdapterArduino::getMode() const {
    return static_cast<uint8_t>(_gpiobase->getMode());
}

bool AdapterArduino::isPinInverted() const {
    return _gpiobase->isPinInverted();
}