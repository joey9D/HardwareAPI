/*
 * esp32c6devkitc.hpp
 *
 *  Created on: Aug 1, 2025
 *      Author: jan.kristel
 */

#ifndef __ESP32C6DEVKITC_HPP
#define __ESP32C6DEVKITC_HPP

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "hw_interface.hpp"

#ifdef __cplusplus

class Esp32c6_hw : public HardwareInterface
{
public:
    void init_sys() override;
    void init_clock() override;
    void delay(uint32_t ms) override;

    void initAllPins() override;

    // ESP32-specific member functions (C++ style)
    uint32_t getFreeHeapSize() const;
    uint32_t getMinimumFreeHeapSize() const;
    void restart() const;
};

#endif /* __cplusplus class */

#endif /* __ESP32C6DEVKITC_HPP */
