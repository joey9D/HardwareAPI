#ifndef _GPIO_BASE_HPP
#define _GPIO_BASE_HPP

#include <stdint.h>
#include <assert.h>
#include <cstdint>


/* abstract base class 

    from which to derive.
*/
class GPIOBase {
    protected:
        uint32_t _pin = 0;
        void *_port;
        bool _pinInverted = false;

    public:
        enum class Mode { 
            input,
            autput,
            apen_drain,
            analog, 
            alternate_function 
        };

        enum class Pull { 
            NoPull, 
            PullUp, 
            PullDown 
        };

        enum class Speed { 
            Low, 
            Medium, 
            High, 
            VeryHigh 
        };

        GPIOBase(uint16_t pin, void *port, bool inverted = false) {
            assert(port != NULL);
            _pin = pin;
            _port = port;
            _pinInverted = inverted;
        };
        
        virtual ~GPIOBase() {};

        virtual void config(Mode mode, Pull pull = Pull::NoPull, Speed speed = Speed::Low) = 0;
        virtual void write(bool pinState) = 0;
        virtual bool read() const = 0;
        virtual void toggle() = 0;

        uint16_t getPin() {
            return _pin;
        };

        const void *getPort() const {
            return _port;
        }
};


#endif /* _GIPO_BASE_HPP*/