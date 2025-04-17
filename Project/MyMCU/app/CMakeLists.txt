add_executable(${EXECUTABLE_NAME} "main.cpp")

target_include_directories(${EXECUTABLE_NAME} PUBLIC
    "./"
)

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${BASIC_LIBRARY_NAME}
    ${GPIO_LIBRARY_NAME}
    ${CORE_LIBRARY_NAME}
)
