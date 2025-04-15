set(LIBRARY_SOURCES
    "gpio_print.cpp"
)

set(LIBRARY_HEADERS
    "gpio.h"
    "gpio_print.h"
)

add_library(${GPIO_LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS}
)

target_include_directories(${GPIO_LIBRARY_NAME} PUBLIC
    "./"
)

target_link_libraries(${GPIO_LIBRARY_NAME} PRIVATE
    ${PERIPH_HEADER_LIBRARY_NAME}

)
