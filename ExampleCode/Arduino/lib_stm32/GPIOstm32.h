#ifndef GPIOstm32_h
#define GPIOstm32_h

#include "GPIObase.h"
//#include <stm32g0xx_hal.h>

class GPIOstm32 : public GPIObase {
    private:
        // uint32_t _pull;
        // uint32_t _speed;
        // uint32_t _alternate;
        GPIO_TypeDef* _port;
    public:
        GPIOstm32(uint32_t pin, uint32_t mode, GPIO_TypeDef *port, bool pinInverted);
        ~GPIOstm32() = default;
        static void init();
        // uint32_t getPull() const;
        // uint32_t getSpeed() const;
        // uint32_t getAlternate() const;
        GPIO_TypeDef* getPort() const;
};


#endif /* END GPIOstm32 */