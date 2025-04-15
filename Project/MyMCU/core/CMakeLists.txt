# set(CORE_SOURCES

# )

set(CORE_HEADERS
    "systick.h"
)

add_library(${CORE_LIBRARY_NAME} INTERFACE

)

target_include_directories(${CORE_LIBRARY_NAME} INTERFACE
    "./"
)
