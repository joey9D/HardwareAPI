#include "RS485Receiver.h"
// #include "usart.h" // todo receive from hardware abstraction layer , layer must be added in the abstraction layer.

bool RS485Receiver::tryReceive(RS485Frame& outFrame) {
     std::array<uint8_t, RS485_FRAME_LEN> buffer;
    // if (HAL_UART_Receive(&huart1, buffer.data(), RS485_FRAME_LEN, 5) == HAL_OK) {
    //     return RS485Protocol::decode(buffer, outFrame);
    // }
    // For now, always return false (hardware abstraction needed)
    return false;
}
// The function tries to receive a complete RS485 frame from the UART interface.
