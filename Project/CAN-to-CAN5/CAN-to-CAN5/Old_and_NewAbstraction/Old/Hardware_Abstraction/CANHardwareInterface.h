#ifndef CAN_HARDWARE_INTERFACE_H
#define CAN_HARDWARE_INTERFACE_H
#ifdef __cplusplus

class CANHardwareInterface {
public:
    // Initialize the CAN hardware
    virtual void CAN_Init() = 0;

    // Start the CAN hardware
    virtual void CAN_Start() = 0;

    // Transmit data through CAN
    virtual void CAN_Transmit(const char* data, int length) = 0;

    // Receive data through CAN
    virtual void CAN_Receive(char* buffer, int length) = 0;

    // Read the state of a GPIO pin
    virtual bool GPIO_Read(int pin) = 0;

    // Set the state of a GPIO pin
    virtual void GPIO_Write(int pin, bool value) = 0;

    // Get the system tick count
    virtual unsigned long GetTick() = 0;

    // Virtual destructor
    virtual ~CANHardwareInterface() {}
};

#endif // __cplusplus


#endif // CAN_HARDWARE_INTERFACE_H
