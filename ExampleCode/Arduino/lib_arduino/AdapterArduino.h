#ifndef AdapterArduino_h
#define AdapterArduino_h

#include <GPIObase.h>
//#include <memory>

class AdapterArduino {
    private:
        //std::unique_ptr<GPIObase> gpiobase;
        GPIObase* _gpiobase;
    public:
        AdapterArduino(GPIObase *gpiobase);
        ~AdapterArduino();
        uint8_t getPin() const;
        uint8_t getMode() const;
        bool isPinInverted() const;
};

#endif /* END AdapterArduino */
