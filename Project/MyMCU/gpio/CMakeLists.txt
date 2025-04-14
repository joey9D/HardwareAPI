add_library(${GPIO_LIBRARY_NAME} STATIC "gpio_print.cpp")

target_include_directories(${GPIO_LIBRARY_NAME} PUBLIC
    "./"
)

target_link_libraries(${GPIO_LIBRARY_NAME} PRIVATE
    ${PERIPH_HEADER_LIBRARY_NAME}

)
