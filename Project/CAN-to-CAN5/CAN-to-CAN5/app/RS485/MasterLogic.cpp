#include "RS485Sender.h"
#include "RS485Receiver.h"
#include "RS485Protocol.h"







void pollCycle() {
    for (uint8_t node = 1; node <= 16; ++node) {
        RS485Sender::sendPoll(node);

        RS485Frame frame;
        bool received = false;
        uint32_t start = HAL_GetTick();
        const uint32_t TIMEOUT_MS = 10; // Wait up to 10 ms for a response

        // Wait for a response or timeout
        while ((HAL_GetTick() - start) < TIMEOUT_MS) {
            if (RS485Receiver::tryReceive(frame)) {
                received = true;
                break;
            }
        }

        if (received) {
            if (frame.type == RS485Type::Button && frame.action == 0x01) {
                // Button pressed, trigger sync LED blink on all nodes
                RS485Sender::sendLED(0xFF, static_cast<uint8_t>(RS485Action::Blink), static_cast<uint8_t>(RS485Color::Green), 200);
            }
            // Optionally handle Ack or other responses here
        }

        // Short pause between polls (optional, e.g., 2 ms)
        // HAL_Delay(2);
    }
}
