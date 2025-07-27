# Drivers module - HAL wrapper for platform-specific drivers
# This module provides a unified interface to native HALs (ESP-IDF, STM32-HAL)

# Platform-specific HAL integration - ESP32 DISABLED
# if(TARGET_PLATFORM STREQUAL "ESP32")
#     # ESP-IDF HAL wrapper
#     add_subdirectory(esp32_hal_wrapper)
    
if(TARGET_PLATFORM STREQUAL "STM32")
    # STM32 HAL wrapper
    add_subdirectory(stm32_hal_wrapper)
endif()

# Create unified drivers interface
add_library(hw_api_drivers INTERFACE)

target_include_directories(hw_api_drivers INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../core
)

# Link platform-specific driver implementations
# if(TARGET_PLATFORM STREQUAL "ESP32")
#     target_link_libraries(hw_api_drivers INTERFACE esp32_hal_wrapper)
if(TARGET_PLATFORM STREQUAL "STM32")
    target_link_libraries(hw_api_drivers INTERFACE stm32_hal_wrapper)
endif()
