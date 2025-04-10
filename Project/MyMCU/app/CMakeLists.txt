add_executable(${EXECUTABLE_NAME} "main.cpp")

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${BASIC_LIBRARY_NAME}
    ${GPIO_LIBRARY_NAME}
)
