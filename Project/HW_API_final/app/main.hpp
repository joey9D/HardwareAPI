#pragma once

/**
 * include std headers
 */
#include <iostream>
#include <cstring>

/**
 * @file main.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-08-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "hw_factory.hpp"
// hw_interface.hpp is included via hw_factory.hpp - no need to include directly
#include "project_config.hpp"

// Platform-specific includes
#ifdef STM32_PLATFORM
#include "../HW_API/drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "spi_stm32.hpp"  // SPI-Klasse für STM32
#include "gpio_stm32.hpp" // GPIO-Klasse für STM32
#elif ESP32_PLATFORM
#include "../HW_API/drivers/esp32_hal_wrapper/esp32_hal_inc.hpp"
#endif
