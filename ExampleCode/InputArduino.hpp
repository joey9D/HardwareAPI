#ifndef InputArduino_h
#define InputArduino_h

#include <lib_arduino/GPIOarduino.h>

class InputArduino : public GPIOarduino {
    private:

    public:
        InputArduino();
        ~InputArduino() = default;
        
}

#endif /* END InputArduino_h */