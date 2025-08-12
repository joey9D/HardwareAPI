#pragma once

#ifdef STM32_PLATFORM
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#endif

#include "spi_interface.hpp"

class Spi : public ISpi
{
public:
    Spi(
        uint16_t pinSCK, Port portSCK,
        uint16_t pinMISO, Port portMISO,
        uint16_t pinMOSI, Port portMOSI,
        uint16_t pinCS = 0, Port portCS = Port::A) // CS optional

        : sck_(pinSCK, portSCK, Mode::Alternate_Push_Pull, Pull::None, Speed::High, false, 0, 0, ExtiTrigger::None),
          miso_(pinMISO, portMISO, Mode::Alternate_Push_Pull, Pull::None, Speed::High, false, 0, 0, ExtiTrigger::None),
          mosi_(pinMOSI, portMOSI, Mode::Alternate_Push_Pull, Pull::None, Speed::High, false, 0, 0, ExtiTrigger::None),
          cs_(pinCS, portCS, Mode::Output_Push_Pull, Pull::Up, Speed::High, false, 0, 0, ExtiTrigger::None)
    {
        sck_.gpio_init();
        miso_.gpio_init();
        mosi_.gpio_init();
        if (pinCS != 0)
            cs_.gpio_init();
    }

    // Implementierung der ISpi-Schnittstelle für STM32
    virtual bool transmit(const uint16_t *data, size_t length) override;
    virtual bool receive(uint16_t *data, size_t length) override;
    virtual bool transmitReceive(const uint16_t *txData, uint16_t *rxData, size_t length) override;

    // DMA
    virtual bool transmit_DMA(const uint16_t *data, size_t length) override;
    virtual bool receive_DMA(uint16_t *data, size_t length) override;
    virtual bool transmitReceive_DMA(const uint16_t *txData, uint16_t *rxData, size_t length) override;

    // Interrupt
    virtual bool transmit_IT(const uint16_t *data, size_t length) override;
    virtual bool receive_IT(uint16_t *data, size_t length) override;
    virtual bool transmitReceive_IT(const uint16_t *txData, uint16_t *rxData, size_t length) override;

private:
    Gpio sck_;
    Gpio miso_;
    Gpio mosi_;
    Gpio cs_; // optional
};
