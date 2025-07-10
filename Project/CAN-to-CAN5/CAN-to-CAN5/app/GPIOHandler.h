#ifndef GPIOHANDLER_H_
#define GPIOHANDLER_H_

// #include "CANopenServices.h"

#include "FunctionMapping.h"
#include <Hardware_Factory.h>
#include <vector>
#include <memory>
#include <array>
#include <queue>
#include "CiA417_CmdHandler.h"
#include "COL_EventTypes.h"
#include "Updated_IO/HeaderFiles/COL_EventSubject.h"
#include "Stack_Fifo.h"
#include "PDO_SDO.h"
#include "helper_functions.h"



#define NUMBER_OF_CLAMPS 1 // Find Central place to define everything
// class CANopenNode;


class GPIOHandler 
{

public:
    GPIOHandler(PDO_SDO* pdo, HardwareInterface* hardware); // Declare the default constructor
    // void init(const CANopenServices& services);


    
    void initializeObservers(FunctionMapping<PinInfo, 8>& inputMap, FunctionMapping<PinInfo, 8>& outputMap);
    void MapIOPins();
    void InputPins();
    void OutputPins();
    libCOL_input_t convertToInput(const virtualIOMapping_data_t& src);
    libCOL_output_t convertToOutput(const virtualIOMapping_data_t& src);
    virtualIOMapping_data_t convertToVirtualIOMapping(const libCOL_input_t& in);
    void execSingleObserverInputPin(uint8_t index);
    // void registerPin(uint16_t pinMask, uint8_t index);
    // void initInterrptMap();
    void InterruptGPIOInputHandler();
    bool isEqualExcludingData(const virtualIOMapping_data_t& a, const virtualIOMapping_data_t& b);
    void onShiftRegisterInputChange(uint8_t index, bool logicalState);
    static void HandleInput(GPIOHandler* instance ,const libCOL_input_t& in);
    void PinInterruptHandler( uint8_t logicalIndex);
    std::queue<uint8_t> inputEventQueue;
    
    


private:
    // const CANopenServices* _svc = nullptr;  // Pointer, not copy
    FunctionMapping<PinInfo, 8> _InputMap;
    FunctionMapping<PinInfo, 8> _OutputMap;
    inline static ODLogger odLogger;
    inline static MyRPDOObserver rpdoHandler;
    size_t inputObserverCount  = 0;
    size_t outputObserverCount = 0;
    inline static MyRPDOObserver rpdoObs;
    static constexpr size_t MaxObservers = 8;
    MyInputObserver  inputObserverList[MaxObservers];
    MyOutputObserver outputObserverList[MaxObservers];

    bool inputNotificationFlag  = false;
    bool outputNotificationFlag = false;
    HardwareInterface* hardware = nullptr; // Instance of the HardwareInterface class to manage hardware functionalities
    PDO_SDO* pdo_sdo = nullptr; // Instance of the PDO_SDO class to manage PDO and SDO operations
    HelperFunctions help;
    CiA417_CmdHandler _CmdHandlers;
};
#endif // GPIOHANDLER_H_
