#ifndef GPIOarduino_h
#define GPIOarduino_h

#include "GPIObase.h"
//#include <Arduino.h>


class GPIOarduino : public GPIObase {
    public:
        GPIOarduino(uint8_t pin, uint8_t mode, bool pinInverted);
        ~GPIOarduino() = default;
        void init();
};

#endif /* END GPIOarduino_HPP */