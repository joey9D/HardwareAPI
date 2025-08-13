#pragma once

/**
 * include std headers
 */
#include <iostream>

/**
 * include HW_API headers - updated for new structure
 */
#include "hw_factory.hpp"
// hw_interface.hpp is included via hw_factory.hpp - no need to include directly
#include "project_config.hpp"

// Platform-specific includes
#ifdef STM32_PLATFORM
#include "../HW_API/drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#elif ESP32_PLATFORM
#include "../HW_API/drivers/esp32_hal_wrapper/esp32_hal_inc.hpp"
#endif
