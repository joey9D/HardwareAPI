add_executable(Blink_exec main.cpp)

target_link_libraries(Blink_exec PUBLIC
    Core
    STM32G0xx_HAL_Driver
    CMSIS
    GPIO
)