add_library(periph_stm32c0 STATIC
    src/*.c
    src/*.cpp
)

target_include_directories(periph_stm32c0 PUBLIC
    include
)

add_subdirectory(CMSIS)

target_link_libraries(periph_stm32c0
    PRIVATE
        periph
        cmsis
)
