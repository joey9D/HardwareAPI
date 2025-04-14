add_library(${PERIPH_HEADER_LIBRARY_NAME} INTERFACE)

target_include_directories(periph INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
