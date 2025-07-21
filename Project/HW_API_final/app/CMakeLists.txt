add_executable(${EXECUTABLE_NAME} "main.cpp")

target_include_directories(${EXXECUTABLE_NAME} PUBLIC "./")

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${CORE_LIB}
    ${GPIO_LIB}
)