add_library(${CORE_LIB} STATIC 
# add cpp files
    "core_test.cpp"
)

target_include_directories(${CORE_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/HW_API)