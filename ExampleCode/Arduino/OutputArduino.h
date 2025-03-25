#ifndef OutputArduino_h
#define OutputArduino_h

#include "lib_arduino/GPIOarduino.h"

class OutputArduino : public GPIOarduino {
    private:
        bool _oldPinState = true;
    public:
        OutputArduino(uint8_t pin, uint8_t mode, bool pinInverted);
        ~OutputArduino() = default;
        bool isOutputPinOn() const;
        void setPinOutput(bool activePinState);
        void toggle();
};

#endif /* END OutputArduino */