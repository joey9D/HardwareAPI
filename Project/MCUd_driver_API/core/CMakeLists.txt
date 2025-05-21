add_library(${CORE_LIBRARY} INTERFACE)

target_include_directories(${CORE_LIBRARY} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
