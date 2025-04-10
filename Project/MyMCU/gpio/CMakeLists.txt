add_library(${GPIO_LIBRARY_NAME} STATIC "gpio_print.cpp")

target_include_directories(${GPIO_LIBRARY_NAME} PUBLIC
    "./"
)
