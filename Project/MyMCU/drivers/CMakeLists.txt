# NOTE:
# This driver directory is/(should be) only temporary.
# Will be changed/removed in the future.

set(DRIVERS_SOURCES
    "dataflash.cpp"
    "dht.cpp"
    "ds18b20.cpp"
    "encoder.cpp"
    "hd44780.cpp"
    "nrf24l01.cpp"
    "onewire.cpp"
    "sd_spi.cpp"
    "sd.cpp"
    "singlewire.cpp"
)
set(DRIVERS_HEADERS
    "dataflash.hpp"
    "dht.hpp"
    "ds18b20.hpp"
    "encoder.hpp"
    "freertos_wrapper.hpp"
    "hd44780.hpp"
    "nrf24l01.hpp"
    "onewire.hpp"
    "sd_cid_csd_red.hpp"
    "sd_spi.hpp"
    "sd.hpp"
    "singlewire.hpp"
)

add_library(drivers PUBLIC
    ${DRIVERS_SOURCES}
    ${DRIVERS_HEADERS}
)

target_include_directories(drivers PUBLIC
    "./"
)

target_link_libraries(drivers
    PUBLIC

)
