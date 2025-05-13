add_executable(${EXECUTABLE_NAME} "main.cpp")

target_include_directories(${EXECUTABLE_NAME} PUBLIC
    "./"
)

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${BASIC_LIBRARY}
    ${GPIO_LIBRARY}
    ${CORE_LIBRARY}
    ${MCU_DRIVERS_LIBRARY}
)
