set(GPIO_SOURCES
    "gpio_print.cpp"
    "gpio_pin_debouncer.cpp"
)

set(GPIO_HEADERS
    "gpio.h"
    "gpio_print.h"
    "gpio_pin_debouncer.h"
)

add_library(${GPIO_LIBRARY_NAME} STATIC
    ${GPIO_SOURCES}
    ${GPIO_HEADERS}
)

target_include_directories(${GPIO_LIBRARY_NAME} PUBLIC
    "./"
)
