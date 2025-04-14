add_library(${BASIC_LIBRARY_NAME} INTERFACE)

target_include_directories(${BASIC_LIBRARY_NAME} INTERFACE
    "./"
)

target_link_libraries(${BASIC_LIBRARY_NAME} PRIVATE
    ${PERIPH_HEADER_LIBRARY_NAME}

)
