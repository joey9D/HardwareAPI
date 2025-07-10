#include "ArduinoCANHardware.h"

void ArduinoCANHardware::CAN_Init() {
    if (!CAN.begin(500E3)) { // Initialize at 500 kbps
        while (true) {} // Initialization error
    }
}

void ArduinoCANHardware::CAN_Start() {
    // Arduino CAN automatically starts after initialization
}

void ArduinoCANHardware::CAN_Transmit(const char* data, int length) {
    CAN.beginPacket(0x123); // Example ID
    for (int i = 0; i < length; i++) {
        CAN.write(data[i]);
    }
    CAN.endPacket();
}

void ArduinoCANHardware::CAN_Receive(char* buffer, int length) {
    int packetSize = CAN.parsePacket();
    if (packetSize > 0) {
        for (int i = 0; i < packetSize && i < length; i++) {
            buffer[i] = CAN.read();
        }
    }
}

void ArduinoCANHardware::GPIO_Read(int pin) {
    digitalRead(pin);
}

void ArduinoCANHardware::GPIO_Write(int pin, bool value) {
    digitalWrite(pin, value ? HIGH : LOW);
}

unsigned long ArduinoCANHardware::GetTick() {
    return millis();
}
