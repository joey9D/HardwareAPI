# set(CORE_SOURCES

# )

# set(CORE_HEADERS
#     "adc.h"
#     "systick.h"
#     "exti.h"
#     "timer.h"
# )

add_library(${CORE_LIBRARY} INTERFACE

)

target_include_directories(${CORE_LIBRARY} INTERFACE
    "./"
)
