set(CMSIS_LIBRARY "cmsis")
set(STM32C0_SRC "stm32c0_src")

add_library(${STM32C0_SRC}
    STATIC
        src/assert.c
        src/fault_handlers.c
        src/exti_stm32c0.cpp
        src/gpio_stm32c0.cpp
#        src/spi_stm32c0.cpp
        src/systick.cpp
        src/timer_stm32c0.cpp
#        src/uart_stm32c0.cpp
        src/wdt.cpp
)

target_include_directories(${STM32C0_SRC}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/${CMSIS_LIBRARY}/Device/ST/STM32C0xx/Include
)

add_subdirectory(${CMSIS_LIBRARY})

target_link_libraries(${STM32C0_SRC}
    PUBLIC
        ${CORE_LIBRARY}
        ${GPIO_LIBRARY}
        ${CMSIS_LIBRARY}
)
