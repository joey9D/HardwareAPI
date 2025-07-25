# STM32C0 specific implementation
add_library(stm32c0_hw 
    stm32c0_hw.cpp
)

target_include_directories(stm32c0_hw PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
)

target_compile_definitions(stm32c0_hw PUBLIC 
    STM32_PLATFORM
    STM32C0
)

# Link with parent STM32 library
target_link_libraries(stm32c0_hw PUBLIC stm32_hw)
