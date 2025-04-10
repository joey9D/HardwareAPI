add_library(${BASIC_LIBRARY_NAME} STATIC "addition.cpp")

target_include_directories(${BASIC_LIBRARY_NAME} PUBLIC
    "./"
)
