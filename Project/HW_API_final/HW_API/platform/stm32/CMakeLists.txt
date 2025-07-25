# STM32 platform-specific hardware implementation
add_library(stm32_hw 
    stm32c0/stm32c0_hw.cpp
)

target_include_directories(stm32_hw PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32c0
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

# STM32 specific compile definitions
target_compile_definitions(stm32_hw PUBLIC 
    STM32_PLATFORM
    STM32C0
)

# Link with HAL library (provides HAL functions for stm32c0_hw.cpp)
target_link_libraries(stm32_hw PUBLIC stm32_hal_wrapper)

# Create subdirectory targets for specific MCU variants
add_subdirectory(stm32c0)