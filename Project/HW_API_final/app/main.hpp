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
#include "project_config.hpp"

// Platform-specific includes
#ifdef STM32_PLATFORM
#include "../HW_API/drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
// #include "../HW_API/spi/hw_linker.hpp"
#include "hw_linker.hpp"
#include "spi_stm32.hpp"
#include "dma_stm32.hpp"
#include "gpio_stm32.hpp"
#elif ESP_PLATFORM
#include "../HW_API/drivers/esp32_hal_wrapper/esp32_hal_inc.hpp"
#endif
