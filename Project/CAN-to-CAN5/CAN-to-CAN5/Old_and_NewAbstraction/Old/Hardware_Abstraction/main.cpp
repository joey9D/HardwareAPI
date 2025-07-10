#include "CANHardwareFactory.h"
#include <iostream>

int main() {
    // Example: Read platform from configuration or environment
    std::string platform = "Zephyr";  // Set to your desired platform ("Zephyr", "STM32", "PIC", etc.)

    // Create hardware instance using factory
    CANHardwareInterface* hardware = CANHardwareFactory::CreateHardware(platform);

    if (!hardware) {
        std::cerr << "Unsupported platform: " << platform << std::endl;
        return -1;
    }

    // Initialize and start the hardware
    hardware->CAN_Init();
    hardware->CAN_Start();

    // Example usage: Transmit and receive data
    const char* message = "Hello CAN!";
    hardware->CAN_Transmit(message, strlen(message));

    char buffer[8] = {0};
    hardware->CAN_Receive(buffer, sizeof(buffer));

    std::cout << "Received: " << buffer << std::endl;

    // Clean up
    delete hardware;
    return 0;
}
