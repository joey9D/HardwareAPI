// RS485Protocol.cpp
#include "RS485Protocol.h"

uint8_t RS485Protocol::computeCRC(const RS485Frame& f) {
    return f.node_id ^ static_cast<uint8_t>(f.type) ^ f.action ^ f.color ^ (f.delay_ms >> 8) ^ (f.delay_ms & 0xFF);
}

bool RS485Protocol::encode(const RS485Frame& f, std::array<uint8_t, RS485_FRAME_LEN>& out_buf) {
    out_buf[0] = RS485_START;
    out_buf[1] = f.node_id;
    out_buf[2] = static_cast<uint8_t>(f.type);
    out_buf[3] = f.action;
    out_buf[4] = f.color;
    out_buf[5] = (f.delay_ms >> 8) & 0xFF;
    out_buf[6] = f.delay_ms & 0xFF;
    out_buf[7] = computeCRC(f);
    out_buf[8] = RS485_END;
    return true;
}

bool RS485Protocol::decode(const std::array<uint8_t, RS485_FRAME_LEN>& in_buf, RS485Frame& f) {
    if (in_buf[0] != RS485_START || in_buf[8] != RS485_END)
        return false;

    uint8_t crc = in_buf[1] ^ in_buf[2] ^ in_buf[3] ^ in_buf[4] ^ in_buf[5] ^ in_buf[6];
    if (crc != in_buf[7])
        return false;

    f.node_id = in_buf[1];
    f.type = static_cast<RS485Type>(in_buf[2]);
    f.action = in_buf[3];
    f.color = in_buf[4];
    f.delay_ms = (in_buf[5] << 8) | in_buf[6];

    return true;
}
// RS485Protocol.cpp
