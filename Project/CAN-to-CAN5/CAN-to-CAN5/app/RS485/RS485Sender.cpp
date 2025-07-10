#include "RS485Sender.h"

void * RS485Sender::_uart = nullptr;
void* RS485Sender::_dePort = nullptr;
uint16_t RS485Sender::_dePin = 0;

void RS485Sender::init(void* uart, void* dePort, uint16_t dePin) {
    _uart = uart;
    _dePort = dePort;
    _dePin = dePin;
}

void RS485Sender::setTX(bool enable) {
    //HAL_GPIO_WritePin(_dePort, _dePin, enable ? GPIO_PIN_SET : GPIO_PIN_RESET); // todo replace with hardware abstraction layer
}

bool RS485Sender::sendFrame(const RS485Frame& frame) {
    std::array<uint8_t, RS485_FRAME_LEN> buffer;
    if (!RS485Protocol::encode(frame, buffer)) return false;

    setTX(true);
    // HAL_UART_Transmit(_uart, buffer, RS485_FRAME_LEN, HAL_MAX_DELAY); // todo replace with hardware abstraction layer
    setTX(false);
    return true;
}

void RS485Sender::sendPoll(uint8_t nodeId) {
//    RS485Frame frame = { nodeId, RS485_POLL, 0, 0, 0 };
//    sendFrame(frame);
}

void RS485Sender::sendLED(uint8_t nodeId, uint8_t action, uint8_t color, uint16_t delay_ms) {
    RS485Frame frame = { nodeId, RS485Type::LED, static_cast<uint8_t>(action), static_cast<uint8_t>(color), delay_ms };
    sendFrame(frame);
}
