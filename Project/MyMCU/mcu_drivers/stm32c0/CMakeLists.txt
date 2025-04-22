add_library(periph_stm32c0 STATIC
    src/assert.c
    src/fault_handlers.c
    src/exti_stm32c0.cpp
    src/gpio_stm32c0.cpp
    src/spi_stm32c0.cpp
    src/systick.cpp
    src/timer_stm32c0.cpp
    src/usart_stm32c0.cpp
    src/wdt.cpp
)

target_include_directories(periph_stm32c0 PUBLIC
    include
)

add_subdirectory(CMSIS)

target_link_libraries(periph_stm32c0
    PRIVATE
        periph
        cmsis
)
