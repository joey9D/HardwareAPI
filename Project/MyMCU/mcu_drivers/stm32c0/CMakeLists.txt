set(CMSIS_LIBRARY_NAME "cmsis")
set(STM32C0_SRC "src")

add_library(${STM32C0_SRC}
    STATIC
        src/assert.c
        src/fault_handlers.c
        src/exti_stm32c0.cpp
        src/gpio_stm32c0.cpp
        src/spi_stm32c0.cpp
        src/systick.cpp
        src/timer_stm32c0.cpp
        src/uart_stm32c0.cpp
        src/wdt.cpp
)

target_include_directories(${STM32C0_SRC}
    PUBLIC
        include
)

add_subdirectory(${CMSIS_LIBRARY_NAME})

target_link_libraries(${STM32C0_SRC}
    PUBLIC
        periph
        ${CMSIS_LIBRARY_NAME}
        ${CORE_LIBRARY_NAME}
)
