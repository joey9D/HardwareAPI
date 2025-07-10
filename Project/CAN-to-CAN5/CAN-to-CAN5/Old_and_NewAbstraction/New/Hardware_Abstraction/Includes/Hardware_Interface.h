#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H


#include <cstdint>
#include "delegate/delegate.hpp"
#include <array>


#define NUM_INPUTS  1
#define NUM_OUTPUTS 1

#define REGISTER_IO

// Enums for GPIO modes and states
enum GPIO_Mode {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_ALTERNATE = 2,
    GPIO_MODE_ANALOG = 3,
    GPIO_MODE_IT_FALLING =4,
    GPIO_MODE_IT_RISING = 5

};

enum GPIO_State
{
    GPIO_LOW = 0,
    GPIO_HIGH = 1
};

enum HardwareError { HW_ERROR_NONE, HW_ERROR_CAN_BUS_OFF, HW_ERROR_CAN_PASSIVE };

enum class VirtualPinSource
{
    PinDirect,
    ShiftRegister,
    RemoteIO, // future
};

struct PinInfo
{

    uint8_t id; // Unique ID for the pin
    bool inverted; // Inversion flag for the pin
    uint32_t debounceTime; // Debounce time in milliseconds
    uint8_t debounceState = 0; // 0: no change, 1: stable low, 2: stable high
    uint32_t lastDebounceTime = 0; // Last debounce time in milliseconds
    bool lastLogicalState = false; // Last logical state of the pin (after inversion)
    VirtualPinSource virtualSource = VirtualPinSource::PinDirect; // Source of the virtual pin
    uint8_t virtualIndex = 0; // for shift register bit index
};

template <typename T, uint8_t N>
class FunctionMapping;
class GPIOHandler;
class NKET_Handler;

using PinInterruptCallback = delegate<void(uint8_t)>; // Callback type for pin interrupts 
using CANInterruptCallback = delegate<void( const uint8_t*, uint32_t)>; // Callback type for CAN interrupts
class HardwareInterface 
{

public:
    


    // CANopenNode
    virtual int CANopen_Init() = 0;              ///< Initialize CANopenNode
    virtual void CANopen_Process() = 0;           ///< Process CANopenNode tasks
    virtual uint32_t CANopen_Reset() = 0;             ///< Reset CANopenNode state
    virtual void CANopen_Interrupt() = 0;         ///< Handle CANopenNode interrupt
    virtual void* getRPDO()=0;
    virtual void getTPDOsend()=0; ///< Get TPDO pointer
    virtual void* getRPDOwithIndex(uint8_t index) = 0; ///< Send TPDO message
    virtual void* getSDO() = 0; ///< Get SDO pointer
    virtual uint8_t getLedgreenstate() = 0; ///< Get green LED state
    virtual uint8_t getLedredstate() = 0; ///< Get red LED state
    virtual void* getNMT() = 0; ///< Get NMT pointer
    virtual bool isIdValid() = 0; ///< Check if node ID is valid
    virtual void getstate(int state) = 0; ///< Get node state

    // CANopenNode Master
    virtual void MasterNodesendCommand(int command , int nodeId = 0) ///< Reset the master node
    {
        // Implement the master node reset command
        // This function can be overridden in derived classes to provide specific implementations
    }
    virtual bool getNMTinternalstate(int state)
    {



    }
    virtual void setNMTinternalstate(int state)
    {

    }
    virtual void RegisterMasterCallbacks()
    {
        // Register callbacks for master node events
        // This function can be overridden in derived classes to provide specific implementations
    }

    virtual void NodeStateHandler()
    {
        // Handle node state changes
        // This function can be overridden in derived classes to provide specific implementations
        // This function makes sure that node id remains valid after reset and no node remains in pre-operational state
    }

    // Core System
    virtual void Clock_Init() = 0;                      ///< Initialize the system clock
    virtual void Delay(uint32_t ms) = 0;               ///< Delay in milliseconds
    virtual uint32_t GetTick() = 0;                    ///< Get system tick count
    virtual void HandlePinInterrupt(uint16_t pin) = 0; ///< Handle pin interrupt
    virtual void ConfigureEXTIInterrupt(const PinInfo& pinCfg) =0;
    //virtual void Init(GPIOHandler* gpioHandler,MainApp* mainApp,FunctionMapping<PinInfo, 8>* inputMap)=0;
    virtual void Init()=0;
    virtual void toggle(void* port, uint16_t pin) = 0; // Pure virtual function
    

    // GPIO
    virtual void GPIO_SetMode(void* port, uint8_t pin, GPIO_Mode mode) = 0; ///< Configure GPIO pin mode
    virtual bool GPIO_Read(const PinInfo& pin) = 0;                    ///< Read GPIO pin state
    virtual void GPIO_Write(const PinInfo& pin, GPIO_State state) = 0;
    virtual void setpinDirection(int clamp, bool output) =0;
    virtual bool GPIOPinInput(int clamp) =0;
    virtual void GPIOPinOutput(int clamp, bool state) =0;
    virtual PinInfo returnPinInput(int clamp) =0;
    virtual PinInfo returnPinOutput(int clamp) =0;
    virtual void GreenLed(bool state)=0;
    virtual void RedLed()=0;
    virtual bool updateDebounce(PinInfo& pinCfg, bool newState) =0;
    virtual void pollShiftRegisterInputs() =0; ///< Poll shift register inputs
    virtual void registerPinInterruptCallback(PinInterruptCallback cb) = 0; ///< Register a callback for pin interrupts

    

    // CAN
    virtual void CAN_Init(uint8_t bus, uint32_t baudrate) = 0;                ///< Initialize CAN bus
    virtual void CAN_Send(uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) = 0; ///< Send CAN message
    virtual bool CAN_Receive(uint8_t bus, uint32_t& id, uint8_t* buffer, uint8_t& len) = 0; ///< Receive CAN message
    virtual void CAN_ConfigFilter(uint8_t bus, uint32_t id, uint32_t mask) = 0; ///< Configure CAN filter
    virtual void errorHandler() = 0; ///< Error handler	
    virtual void LEDblink(bool state) =0; ///< Blink LED
    virtual void setHandles(int nodeId = 17) =0; ///< Set hardware handles for CANopenNode

    // Special Hardware / project Specific Functions
    virtual int initandSetFilters(const std::array<uint32_t,13>& arr) ///< Register CAN ID filters ,May or Maynot be overrriden
    {
        // Default implementation does nothing
        // Derived classes can override this to register CAN ID filters
         // Return 0 for success, or an error code if needed
    }
    virtual void CANerrorHandler()
    {


    } ///< Handle CAN errors
    virtual void RegisterCANInterruptCallback(CANInterruptCallback cb) ///< Register a callback for CAN interrupts
    {
        // Default implementation does nothing
        // Derived classes can override this to handle CAN interrupts
        // This function can be overridden in derived classes to provide specific implementations
    }
    virtual bool allNodesBooted()
    {
        // Default implementation returns false
        // Derived classes can override this to check if all nodes are booted
        // Return true if all nodes are booted, false otherwise
        return false;
    }

    // TFT/Display
    virtual void TFT_Init(uint16_t width, uint16_t height) = 0;               ///< Initialize TFT display
    virtual void TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) = 0;   ///< Draw a pixel on TFT
    virtual void TFT_FillScreen(uint16_t color) = 0;                          ///< Fill the screen with a color
    virtual bool TFT_TouchGetXY(uint16_t& x, uint16_t& y) = 0;                ///< Get touch coordinates

    // Wireless (WB/WL)
    #ifdef ENABLE_WIRELESS
    virtual void BLE_Init() = 0;                                              ///< Initialize BLE
    virtual void LoRa_Send(uint8_t* data, uint8_t len) = 0;                   ///< Send LoRa message
    #endif

    // Advanced Peripherals
    virtual void ADC_Start(uint8_t channel) = 0;                              ///< Start ADC conversion
    virtual uint16_t ADC_Read(uint8_t channel) = 0;                           ///< Read ADC value
    virtual void PWM_Set(uint8_t timer, uint8_t channel, uint16_t value) = 0; ///< Set PWM value

    // Multi-core (H7/MP)
    virtual void M4_Core_Start(void (*func)(void)) = 0;                       ///< Start M4 core
    virtual void A7_Core_Init() = 0;                                          ///< Initialize A7 core (Linux)

    // Timer
    virtual void Timer_Base_Start_IT(void* htim) = 0; ///< Start timer with interrupt

    // NVIC
    virtual void System_Reset()=0; ///< Reset the system

    virtual ~HardwareInterface() = default;                                   ///< Virtual destructor for cleanup


private:



};
#endif


