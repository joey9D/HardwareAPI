#pragma once

/**
 * include std headers
 */
#include <iostream>

/**
 * include HW_API headers - updated for new structure
 */
#include "hw_factory.hpp"
#include "hw_interface.hpp"
#include "pin_config.hpp"

// Platform-specific includes
#ifdef STM32_PLATFORM
    // STM32 specific headers if needed
#elif ESP32_PLATFORM
    // ESP32 specific headers if needed
#endif
