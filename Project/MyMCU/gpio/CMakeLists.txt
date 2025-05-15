add_library(${GPIO_LIBRARY} STATIC
    "gpio_print.cpp"
    "gpio_pin_debouncer.cpp"
)

target_include_directories(${GPIO_LIBRARY} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
