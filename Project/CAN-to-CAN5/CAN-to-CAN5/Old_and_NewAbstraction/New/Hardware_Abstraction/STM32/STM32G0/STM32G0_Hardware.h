#ifndef STM32G0_HARDWARE_H
#define STM32G0_HARDWARE_H

#include "Hardware_Interface.h"
#include "stm32g0xx_hal.h"
#include "STM32G0_Pins_config.h"
#include <tuple>
#include <array>
#include <cstdint>
#include "ShiftRegisterIO.h"
#include "Hardware_Definitions.h"
extern "C" {
#include "CO_app_STM32.h"
}
#include "globals.h"
#include "Board_Selector.h"

extern ActiveBoardPins boardPins;

class STM32G0_Hardware : public HardwareInterface 
{

public:

STM32G0_Hardware(); // Constructor
    // Core System
void Init() override;
void initAllPins(); ///< Initialize all pins on the board
// canopennode 
int  CANopen_Init() override;              ///< Initialize CANopenNode
void   CANopen_Process() override;           ///< Process CANopenNode tasks
uint32_t CANopen_Reset() override;            ///< Reset CANopenNode state
void CANopen_Interrupt() override ;         ///< Handle CANopenNode interrupt   
inline void* getRPDO() override {return canopenNodeSTM32.canOpenStack->RPDO;}
inline void getTPDOsend() override {canopenNodeSTM32.canOpenStack->TPDO[0].sendRequest = 1; } ///< Get TPDO pointer
inline void* getRPDOwithIndex(uint8_t index) override {return &canopenNodeSTM32.canOpenStack->RPDO[index]; } ///< Send TPDO message
inline uint8_t getLedgreenstate() override {return canopenNodeSTM32.outStatusLEDGreen; } ///< Get green LED state
inline uint8_t getLedredstate() override {return canopenNodeSTM32.outStatusLEDRed; } ///< Get red LED state
inline void* getSDO() override {return canopenNodeSTM32.canOpenStack->SDOserver; } ///< Get SDO pointer
inline void* getNMT() override {return canopenNodeSTM32.canOpenStack->NMT; } ///< Get NMT pointer

bool isIdValid() override; ///< Check if node ID is valid
void getstate(int state) override; ///< Get node state


// Master Operations
void MasterNodesendCommand(int command, int nodeId = 0) override; ///< Reset the master node
void RegisterMasterCallbacks() override; ///< Register callbacks for master node events
bool getNMTinternalstate(int state) override; ///< Get NMT internal state
void setNMTinternalstate(int state) override; ///< Set NMT internal state
void NodeStateHandler() override; ///< Handle node state changes, ensures node ID remains valid after reset and no node remains in pre-operational state
static void onNodeNmtChanged(uint8_t nodeId, uint8_t idx, CO_NMT_internalState_t NMTstate, void *object); ///< Callback for NMT state change

void timingHandler();

void Clock_Init() override;                     ///< Initialize the system clock
void Delay(uint32_t ms) override;               ///< Delay in milliseconds
uint32_t GetTick() override;                    ///< Get system tick count
void HandlePinInterrupt(uint16_t pin) override;
void ConfigureEXTIInterrupt(const PinInfo& pinCfg) override; ///< Configure EXTI interrupt
void toggle(void* port, uint16_t pin) override; // toggle the pin state // Unused in this implementation, but can be used for toggling GPIO pins
void LEDblink(bool state) override;


///< Handle pin interrupt

// GPIO
void GPIO_SetMode(void* port, uint8_t pin, GPIO_Mode mode) override; ///< Configure GPIO pin mode
bool GPIO_Read(const PinInfo& pin) override;                    ///< Read GPIO pin state
void GPIO_Write(const PinInfo& pin, GPIO_State state) override; ///< Write GPIO pin state
void setpinDirection(int clamp, bool output) override;
bool GPIOPinInput(int clamp) override;
void GPIOPinOutput(int clamp, bool state) override;
PinInfo returnPinInput(int clamp) override;
PinInfo returnPinOutput(int clamp) override;
void GreenLed(bool state) override;
void RedLed() override;
bool updateDebounce(PinInfo& pinCfg, bool newState) override;
void registerPinInterruptCallback(PinInterruptCallback cb) override {m_pinInterruptCallback = cb;} ///< Register a callback for pin interrupts


// CAN
void CAN_Init(uint8_t bus, uint32_t baudrate) override;                ///< Initialize CAN bus
void CAN_Send(uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) override; ///< Send CAN message
bool CAN_Receive(uint8_t bus, uint32_t& id, uint8_t* buffer, uint8_t& len) override; ///< Receive CAN message
void CAN_ConfigFilter(uint8_t bus, uint32_t id, uint32_t mask) override; ///< Configure CAN filter;
void errorHandler() override; ///< Error handler
void setHandles(int nodeId = 17) override; ///< Set hardware handles for CANopenNode


// G0 CAN TO CAN Specific implementation

int initandSetFilters(const std::array<uint32_t,13>& arr) override;  ///< Register CAN ID filters
void CANerrorHandler()override;///< Handle CAN errors
void RegisterCANInterruptCallback(CANInterruptCallback cb) override; ///< Register a callback for CAN interrupts
bool allNodesBooted() override; ///< Check if all nodes are booted


// TFT/Display
void TFT_Init(uint16_t width, uint16_t height) override;               ///< Initialize TFT display
void TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) override;   ///< Draw a pixel on TFT
void TFT_FillScreen(uint16_t color) override;                          ///< Fill the screen with a color
bool TFT_TouchGetXY(uint16_t& x, uint16_t& y) override;                ///< Get touch coordinates

// Wireless (WB/WL)
#ifdef ENABLE_WIRELESS
void BLE_Init() override;                                              ///< Initialize BLE
void LoRa_Send(uint8_t* data, uint8_t len) override;                   ///< Send LoRa message
#endif

// Advanced Peripherals
void ADC_Start(uint8_t channel) override;                              ///< Start ADC conversion
uint16_t ADC_Read(uint8_t channel) override;                           ///< Read ADC value
void PWM_Set(uint8_t timer, uint8_t channel, uint16_t value) override; ///< Set PWM value

// Multi-core (H7/MP)
void M4_Core_Start(void (*func)(void)) override;                       ///< Start M4 core
void A7_Core_Init() override;                                          ///< Initialize A7 core (Linux)


// Timer
void Timer_Base_Start_IT(void* htim) override; ///< Start timer with interrupt

void pollShiftRegisterInputs() override;

// NVIC
void System_Reset() override; ///< Reset the system

// Project Specific Functions
template <size_t N>
HAL_StatusTypeDef Register_FDCAN_ExtendedID_Filters(FDCAN_HandleTypeDef *hfdcan,
                                                    const std::array<uint32_t, N>& ext_ids,
                                                    uint32_t fifo_num);


std::array<bool, 16> extiEnabledPins; ///< Array to track which EXTI pins are enabled
static STM32G0_Hardware* s_instance; //instance of STM32G0_Hardware
CANopenNodeSTM32 canopenNodeSTM32; ///< Pointer to CANopenNode structure
CANInterruptCallback m_canInterruptCallback = nullptr;


private:
    bool checknodestatus = false; ///< Flag to check if node status needs to be checked after set to pre-operational state
    uint8_t index_1016 = 0; ///< index for 1016 for node to be checked CANopenNode, default is 0 this node id will be be checked by the state handler function
    static constexpr size_t MAX_EXTI_PINS = 16;// Maximum number of external interrupt pins supported by the GPIOHandler.
    std::array<int16_t, MAX_EXTI_PINS> pinToIndexLUT; // LUT (Lookup Table) for mapping EXTI lines to application pin indices.
    friend void HAL_GPIO_EXTI_Rising_Callback(uint16_t pin);
    ShiftRegisterIO _shiftIO; ///< Shift register IO handler
    uint8_t _lastShiftInputState = 0x00; ///< Last state of shift register inputs
    bool shiftRegisterFirstPoll = true;  ///< Flag to indicate if this is the first poll of shift register inputs
    PinInfo _shiftRegisterPins[8];           // Debounce tracking for shift register inputs
    HardwareDefinitions hwDefs; // Hardware definitions for CANopenNode
    bool nodestate = false; ///< Node state, true if node is initialized and running
    PinInterruptCallback m_pinInterruptCallback = nullptr; ///< Callback for pin interrupts
    static constexpr uint8_t MAX_NODES = 127;
    // uint32_t lastNmtCommandTime[MAX_NODES];
    bool nmtOpSent[MAX_NODES] = {false};
    inline static CO_HBconsumer_state_t lastHBstate[MAX_NODES] = {CO_HBconsumer_UNKNOWN}; // Or whatever your node ID range is
    struct NodeStatus 
    {
        bool bootup_received = false;
        bool operational = false;
        uint32_t lastNmtCommandTime = 0;
    };
    NodeStatus nodeStatus[128] = {}; ///< Node status array for tracking bootup and operational states


};

#endif
