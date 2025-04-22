set(CMSIS_LIBRARY_NAME )

add_library(cmsis STATIC
    Device/ST/STM32C0xx/Source/system_stm32c0xx.c
)

target_include_directories(cmsis
    PRIVATE
        Core/Include
        Device/ST/STM32C0xx/Include
)

# TODO: Check CubeMX which HSE_VALUE is used/needed.
# target_compile_definitions(cmsis
#     PRIVATE
#         HSE_VALUE=
# )

add_subdirectory(DSP)
add_subdirectory(NN)
