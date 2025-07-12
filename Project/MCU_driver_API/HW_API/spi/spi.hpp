#ifndef __SPI_HPP
#define __SPI_HPP

#ifdef __cplusplus

#include <cstdint>
#include "hw_interface.hpp"
#include "gpio.hpp"


class Spi
{
    public:
        transmit();
        receive();
        transmitReceive();
        transmit_IT();
        receive_IT();
        transmitReceive_IT();
        transmit_DMA();
        receive_DMA();
        transmitReceive_DMA();
    private:

};

#endif /* __cplusplus */
#endif /* __SPI_HPP */
