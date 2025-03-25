#include <lib_arduino/GPIOarduino.h>


GPIOarduino::GPIOarduino(uint8_t pin, uint8_t mode, bool pinInverted)
    : GPIObase(pin, mode, pinInverted) 
{
    // initialization list
}

void GPIOarduino::init() {
    pinMode(getPin(), getMode());
}