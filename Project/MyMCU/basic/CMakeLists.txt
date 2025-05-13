add_library(${BASIC_LIBRARY} INTERFACE)

target_include_directories(${BASIC_LIBRARY} INTERFACE
    "./"
)

target_link_libraries(${BASIC_LIBRARY} INTERFACE
    ${PERIPH_HEADER_LIBRARY}

)
