add_library(periph_stm32c0 STATIC
    src/
)

add_subdirectory(CMSIS)

target_link_libraries(periph_stm32c0 PUBLIC

)
