/**
 * @file spi_esp32.cpp
 * @author Jan Kristel
 * @brief Spi implementation for ESP32
 * @version 0.1
 * @date 2025-09-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "spi_esp32.hpp"
#include "../drivers/esp32_hal_wrapper/common/esp32_hal_inc.hpp"

Spi::Spi(
    bool isMaster,
    Gpio &sck,
    Gpio &miso,
    Gpio &mosi,
    Gpio &cs,
    spi_host_device_t host, // spi_types.h

    ) : _isMaster(isMaster),
        _sck(sck),
        _miso(miso),
        _mosi(mosi),
        _cs(cs),
        _host(host)
{
}

Spi::~Spi()
{
}

Spi::spi_init()
{
    switch (_isMaster)
    {
    //=========================== preparing esp32 as master ===========================
    case true:
        // prepareing the bus configuration
        // spi_common.h
        spi_bus_config_t buscfg = {
            .mosi_io_num = -1,
            .miso_io_num = -1,
            .sclk_io_num = -1,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .data4_io_num = -1,
            .data5_io_num = -1,
            .data6_io_num = -1,
            .data7_io_num = -1,
            .max_transfer_sz = -1,
            // uint32_t flags
            // esp_intr_cpu_affinity_t isr_cpu_id
            // int intr_flags
        };

        // preparing slave(device) configuration
        // ESP32 is master
        // external device is slave
        spi_device_interface_config_t slave_cfg = {
            .command_bits = 0,
            .address_bits = 0,
            .dummy_bits = 0,
            .mode = 0, // SPI mode 0
            .duty_cycle_pos = 0,
            .cs_ena_pretrans = 0,
            .cs_ena_posttrans = 0,
            .clock_speed_hz = 1000000, // Clock out at 1 MHz
            .input_delay_ns = 0,
            .spics_io_num = -1,
            .flags = 0,
            .queue_size = 1,
            // .pre_cb = NULL,
            // .post_cb = NULL
        };

        master_init();
        break;
    //=========================== preparing esp32 as slave ===========================
    case false:
        // preparing esp32 as slave
        // external device is master
        spi_slave_interface_t slave_interface = {
            .mode = 0, // SPI mode 0
            .duty_cycle_pos = 0,
            .cs_ena_pretrans = 0,
            .cs_ena_posttrans = 0,
            .clock_speed_hz = 1000000, // Clock out at 1 MHz
            .input_delay_ns = 0,
            .spics_io_num = -1,
            .flags = 0,
            .queue_size = 1,
            // .pre_cb = NULL,
            // .post_cb = NULL
        };

        slave_init();
    default:
        break;
    }
}