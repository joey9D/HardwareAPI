// RS485Protocol.h
#pragma once

#include <array>
#include <cstdint>

constexpr uint8_t RS485_FRAME_LEN = 9;
constexpr uint8_t RS485_START = 0xAA;
constexpr uint8_t RS485_END = 0x55;

enum class RS485Type : uint8_t 
{
    Poll     = 0x10, // Master asks: "Do you have data?"
    Ack      = 0x12, // Slave: "No, I have nothing"
    Button   = 0x11, // Slave: "Yes, here is the button press"
    LED      = 0x20  // Master sends LED update
};

enum class RS485Action : uint8_t 
{
    Off   = 0x00,
    On    = 0x01,
    Blink = 0xF0
};

enum class RS485Color : uint8_t 
{
    Off    = 0x00,
    Red    = 0x01,
    Green  = 0x02,
    Blue   = 0x03,
    Yellow = 0x04,
    White  = 0x05
};

struct RS485Frame 
{
    uint8_t node_id;        // 0x01–0x10 or 0xFF (broadcast)
    RS485Type type;         // Poll, Ack, Button, LED
    uint8_t action;         // LED state or button state
    uint8_t color;          // LED color
    uint16_t delay_ms;      // Delay in milliseconds
};

class RS485Protocol 
{
public:
    static bool encode(const RS485Frame& f, std::array<uint8_t, RS485_FRAME_LEN>& out_buf);
    static bool decode(const std::array<uint8_t, RS485_FRAME_LEN>& in_buf, RS485Frame& f);

private:
    static uint8_t computeCRC(const RS485Frame& f);
};
