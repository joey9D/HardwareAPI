#include "CO_app_ESP32.h"
#include "esp_timer.h"

CANopenNodeESP32* canopen_node;

void canopen_app_init(CANopenNodeESP32* node) {
    canopen_node = node;
    CO_CANmodule_init(node->canOpenStack->CANmodule, node->can_hw, ...);
    CO_CANsetNormalMode(node->canOpenStack->CANmodule);
}

uint8_t canopen_app_process() {
    static uint64_t last_time = 0;
    uint64_t now = esp_timer_get_time() / 1000;
    if ((now - last_time) >= 1) {
        CO_process(canopen_node->canOpenStack, false, (now - last_time) * 1000, NULL);
        last_time = now;
        return 1;
    }
    return 0;
}
