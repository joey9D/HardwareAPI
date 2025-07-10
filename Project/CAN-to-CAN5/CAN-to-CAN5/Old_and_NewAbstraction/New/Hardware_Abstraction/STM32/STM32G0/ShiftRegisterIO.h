// ShiftRegisterIO.h
#pragma once
#include "stm32G0xx_hal.h"
#include <cstdint>
#include "STM32G0_Pins_config.h"

class ShiftRegisterIO 
{
public:
    void init();
    void writeOutputs(uint8_t data); // For U7
    uint8_t readInputs();            // For U8

    // Optional bit-level helpers
    void setOutputBit(uint16_t index, bool state);
    bool getInputBit(uint16_t index) const;
private:
    void pulse(GPIO_TypeDef* port, uint16_t pin);

    // Define shift register control pins
    static GPIO_TypeDef* const PORTA;
    static GPIO_TypeDef* const PORTB;

    static constexpr uint16_t PIN_STR  = GPIO_PIN_0; // U7 Latch
    static constexpr uint16_t PIN_D0   = GPIO_PIN_7; // U7 Serial Data In
    static constexpr uint16_t PIN_CLK  = GPIO_PIN_6; // Shared Clock
    static constexpr uint16_t PIN_PL   = GPIO_PIN_1; // U8 Parallel Load
    static constexpr uint16_t PIN_PISO = GPIO_PIN_4; // U8 Serial Out

    uint8_t outputState = 0;
    uint8_t inputState = 0;
};

#pragma once
#include <cstdint>

// Template-based shift register
template<typename STR, typename D0, typename CLK, typename PL, typename PISO>
class ShiftRegister 
{
public:
    static void writeOutputs(uint8_t data) {
        for (int i = 0; i < 8; ++i) {
            D0::write(data & (1 << (7 - i)));
            CLK::write(true);
            CLK::write(false);
        }
        STR::write(true);
        STR::write(false);
    }
    static uint8_t readInputs() {
        uint8_t val = 0;
        PL::write(false);
        PL::write(true);
        for (int i = 0; i < 8; ++i) {
            val <<= 1;
            val |= PISO::read() ? 1 : 0;
            CLK::write(true);
            CLK::write(false);
        }
        return val;
    }
};
