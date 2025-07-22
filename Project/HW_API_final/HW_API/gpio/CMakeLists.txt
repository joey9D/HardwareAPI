add_library(${GPIO_LIB} STATIC
# add cpp files
    "gpio_test.cpp"
)

target_include_directories(${GPIO_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/HW_API)