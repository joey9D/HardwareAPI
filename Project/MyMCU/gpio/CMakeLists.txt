set(GPIO_SOURCES
    "gpio_print.cpp"
)

set(GPIO_HEADERS
    "gpio.h"
    "gpio_print.h"
)

add_library(${GPIO_LIBRARY_NAME} STATIC
    ${GPIO_SOURCES}
    ${GPIO_HEADERS}
)

target_include_directories(${GPIO_LIBRARY_NAME} PUBLIC
    "./"
)
