#ifndef OutputSTM32_h
#define OutputSTM32_h

#include "lib_stm32/GPIOstm32.h"

class OutputSTM32 : public GPIOstm32 {
    private:
        bool _oldState = true;
    public:
        OutputSTM32(uint32_t pin, uint32_t mode, GPIO_TypeDef *port, bool pinInverted);
        ~OutputSTM32() = default;
        bool isOutputPinOn() const;
        void setPinOutput(bool activePinState);
        void toggle();
}

#endif /* END OutputSTM32_h */