#pragma once

#ifdef ESP_PLATFORM
#include "../core/hw_enum_classes.hpp"

class Spi : public ISpi
{
public:
    Spi(
        Gpio &sck,
        Gpio &miso,
        Gpio &mosi,
        Gpio &cs,
        spi_host_device_t host,

    );

    // - init
    bool spi_init() override;

    // Polling
    bool transmit(const uint8_t *data, uint16_t length, uint32_t timeout) override;
    bool receive(uint8_t *data, uint16_t length, uint32_t timeout) override;
    bool transmitReceive(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout) override;

private:
    bool _isMaster;
    Gpio &_sck;
    Gpio &_miso;
    Gpio &_mosi;
    Gpio &_cs;

    int _quadwp_io_num;
    int _quadhd_io_num;
    int _max_transfer_size; // spi_common.h default
    uint32_t _bus_flags;    // esp master
    uint32_t _device_flags; // esp master, external slave
    uint32_t _slave_flags;  // esp slave
    uint8_t _mode;          // cpol + cpha: 00=0, 01=1, 10=2, 11=3
    esp_intr_cpu_affinity_t _isr_cpu_id;
    int _intr_flags;
    spi_host_device_t _host; // spi_types.h // SPI2_HOST as default, SPI3_HOST

    spi_clock_source_t _clk_src;
    int clock_speed_hz;

    // TODO: add if needed
    //  uint8_t _command_bits;
    //  uint8_t _address_bits;
    //  uint8_t _dummy_bits;
    //  int _duty_cycle_pos;
    //  int input_delay_ns;
    //  transaction_cb_t post_cb;
    //  transaction_cb_t pre_cb;
    //  int queue_size;

    spi_device_handle_t _handle = nullptr; // spi_master.h
};
