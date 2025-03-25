
#ifndef GPIObase_h
#define GPIObase_h

#include <Arduino.h>
#include <stdint.h>
#include <string.h>

class GPIObase {
  private:
    uint32_t _pin;
    uint32_t _mode;
    bool _pinInverted = false;
  public:
    GPIObase(uint32_t pin, uint32_t mode, bool pinInverted);
    ~GPIObase();

    uint32_t getPin() const;
    uint32_t getMode() const;
    bool isPinInverted() const;
};

#endif /* END MYCLASS */