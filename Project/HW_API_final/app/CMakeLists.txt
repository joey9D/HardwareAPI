add_executable(${EXECUTABLE_NAME} "main.cpp")

target_include_directories(${EXECUTABLE_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${CORE_LIB}
    ${GPIO_LIB}
)