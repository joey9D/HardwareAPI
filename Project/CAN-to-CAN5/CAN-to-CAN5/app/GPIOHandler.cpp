#include "GPIOHandler.h"
#include "CANopenNode.h"

GPIOHandler::GPIOHandler(PDO_SDO* pdo, HardwareInterface* hardware)
    : pdo_sdo(pdo), hardware(hardware)
{
    // Constructor implementation (if needed)
}


void GPIOHandler::HandleInput(GPIOHandler* instance, const libCOL_input_t& in) 
{
    if (in.functionData.raw == 0) 
    {
        return; // Filter out invalid entries
    }
    virtualIOMapping_data_t map = instance->convertToVirtualIOMapping(in); // Use the instance to call non-static methods

    assert(instance != nullptr);
    assert(instance->pdo_sdo != nullptr);

    instance->_CmdHandlers.execInputCmd(map);  // Signal Output Commands
    instance->pdo_sdo->QueueTPDO(map); // Queue the TPDO data for processing
}

void GPIOHandler::PinInterruptHandler(uint8_t logicalIndex)  // Callback function for pin interrupts
{
    // This method is called when a pin interrupt occurs.
    // It pushes the logical index of the pin that triggered the interrupt onto the input event queue.
    // The logical index corresponds to the application pin index, allowing the handler to process it later.
    
    // Push the logical index onto the input event queue for further processing.
    inputEventQueue.push(logicalIndex);
}

void GPIOHandler::MapIOPins()
{ 

    /**
     * Initializes the pin-to-index lookup table that maps EXTI line numbers to their 
     * corresponding application pin indices. This table allows the interrupt handler
     * to quickly determine which application pin was triggered without searching through
     * all registered pins. The table is filled with -1 initially, indicating all pins
     * are unmapped, and later populated by the registerPin() method.
    */
    //initInterrptMap();
    // Create static arrays of input and output objects.
    static PinInfo inputPins[NUMBER_OF_CLAMPS];
    static PinInfo outputPins[NUMBER_OF_CLAMPS];

    // Loop goes over each defined clamp registers it as Input output and also maps it to the pin.
    for (uint8_t i = 0; i < NUMBER_OF_CLAMPS; i++)
    {
        // ----- For Input Pins -----
        // Register the physical input pin.
        inputPins[i] = hardware->returnPinInput(i);
        hardware->ConfigureEXTIInterrupt(inputPins[i]);// Pin Interrupt Configuration
        // Set the pin as input in the hardware layer.
        _InputMap.setPinToMap(inputPins[i]);

        // Register this pin in the map:
        //registerPin(inputPins[i].pin, i);
        // Retrieve the current virtual mapping for this pin from the Object Dictionary (OD) at index 0x6100.
        virtualIOMapping_data_t odInputMapping = help.getODInputFunctionMapping(i);
        // Update the mapping in the FunctionMapping table.
        _InputMap.setFunctionToPin(i, odInputMapping);
        
        // ----- For Output Pins -----
        // Register the physical output pin.
        outputPins[i] = hardware->returnPinOutput(i);
        // Set the pin as output in the hardware layer.
        _OutputMap.setPinToMap(outputPins[i]);
        // Retrieve the current virtual mapping for the output pin from the OD at index 0x6200.
        virtualIOMapping_data_t odOutputMapping = help.getODOutputFunctionMapping(i);
        // Update the mapping in the FunctionMapping table.
        _OutputMap.setFunctionToPin(i, odOutputMapping);
    }
    // Register the pin interrupt callback with the CANopenNode hardware interface.

    //  1. Create a callback object for pin interrupts.
    PinInterruptCallback cb; 

    // 2. Set the callback function to the PinInterruptHandler method of this instance.
    cb.set<GPIOHandler, &GPIOHandler::PinInterruptHandler>(*this); 
    
    // 3. Register the callback with the hardware interface.
    hardware->registerPinInterruptCallback(cb);

    hardware->Init(); // passes library object to the hardware layer , required for interuupt defintion and avoiding circular dependency.
    initializeObservers(_InputMap, _OutputMap); // Initializes observers which logg the TPDO and RPDO data:

}

void GPIOHandler::initializeObservers(FunctionMapping<PinInfo, 8>& inputMap, FunctionMapping<PinInfo, 8>& outputMap) 
{
    inputObserverCount = 0;
    outputObserverCount = 0;

    // handler used here for modularity and to avoid code duplication.
    // This is a static array of observers, so it should be large enough to hold all observers.

    for (uint8_t i = 0; i < inputMap.getPinCount(); ++i) 
    {
        virtualIOMapping_data_t virt = inputMap.getPinMapping(i);
        MyInputObserver& obs = inputObserverList[inputObserverCount++];
        obs.myLiftMask = virt.lift;
        obs.myFloor = virt.floor;
        obs.myDoor = virt.door;

        obs.configure(
            static_cast<libCOL_inputBasicFunction_t>(virt.basicFunction),
            this,
            GPIOHandler::HandleInput  // This matches (GPIOHandler*, const libCOL_input_t&)
        );

        g_eventBus.input.registerObserver(&obs);
    }

    for (uint8_t i = 0; i < outputMap.getPinCount(); ++i) 
    {
        const virtualIOMapping_data_t& virt = outputMap.getPinMapping(i);
        MyOutputObserver& obs = outputObserverList[outputObserverCount++];
        obs.myLiftMask = virt.lift;
        obs.myFloor = virt.floor;
        obs.mydoor = virt.door;

        g_eventBus.output.registerObserver(&obs);
    }

    
    g_eventBus.od.registerObserver(&odLogger);

    for (uint8_t i = 0; i < outputMap.getPinCount(); ++i) 
    {
        const virtualIOMapping_data_t& virt = outputMap.getPinMapping(i);
    
        // Register in RPDO handler
        rpdoObs.addHandler(
            static_cast<libCOL_outputBasicFunction_t>(virt.basicFunction),[](const virtualIOMapping_data_t& map)
            {
                //this->_CmdHandlers.execOutputCmd(map);
                // TODO . add the output fucntion interrupt caller here.
            }
        );
    }
     g_eventBus.rpdo.registerObserver(&rpdoObs);

    
}



virtualIOMapping_data_t GPIOHandler::convertToVirtualIOMapping(const libCOL_input_t& in) 
{
    virtualIOMapping_data_t mapping{};
    mapping.basicFunction = static_cast<uint8_t>(in.basicfunction);
    mapping.subFunction = in.subFunction.raw;
    mapping.lift = in.lift.raw;
    mapping.floor = in.floor;
    mapping.door = in.door.raw;
    mapping.functionData = in.functionData.raw; // assumes raw layout
    return mapping;
}

libCOL_input_t GPIOHandler::convertToInput(const virtualIOMapping_data_t& src) 
{
    libCOL_input_t in{};
    in.basicfunction = static_cast<libCOL_inputBasicFunction_t>(src.basicFunction);
    in.subFunction.raw = src.subFunction;
    in.lift.raw = src.lift;
    in.floor = src.floor;
    in.door.raw = src.door;
    in.functionData.generic.genericState = static_cast<decltype(in.functionData.generic.genericState)>(src.functionData);
    return in;
}

libCOL_output_t GPIOHandler::convertToOutput(const virtualIOMapping_data_t& src) 
{
    libCOL_output_t out{};
    out.basicfunction = static_cast<libCOL_outputBasicFunction_t>(src.basicFunction);
    out.subFunction.raw = src.subFunction;
    out.lift.raw = src.lift;
    out.floor = src.floor;
    out.door.raw = src.door;
    out.functionData.generic.status = src.functionData & 0x1;  // Assuming bit0 is status
    return out;
}

void GPIOHandler::InputPins()  // Polling for Pins (Can be called Continuously in the infinite loop)
{
    for (uint8_t i = 0; i < _InputMap.getPinCount(); ++i) 
    {
        PinInfo* pinCfg = _InputMap.getGpio(i); // hardware GPIO info
        const virtualIOMapping_data& mapping = _InputMap.getPinMapping(i);  // logical OD-mapped function

        bool rawState = hardware->GPIO_Read(*pinCfg); // read the raw state from hardware
        bool logicalState = pinCfg->inverted ? !rawState : rawState;

        bool stateChanged = hardware->updateDebounce(*pinCfg, logicalState); // you must implement this

        if (stateChanged) {
            libCOL_numbered_input_t wrapper;
            wrapper.input = convertToInput(mapping); // conversion function required
            wrapper.number = i;

            g_eventBus.input.notifyInput(wrapper);
        }
    }
}


// ===== Output update from OD + observer trigger (Observer Version) =====
void GPIOHandler::OutputPins() 
{
    for (uint8_t i = 0; i < _OutputMap.getPinCount(); ++i) 
    {
        PinInfo* pinCfg = _OutputMap.getGpio(i);
        const virtualIOMapping_data& mapping = _OutputMap.getPinMapping(i);

        bool desiredState = static_cast<bool>(mapping.functionData); // Assuming functionData is a bitmask where the first bit is the desired state
        // Check if the desired state is different from the current state //?????????
        bool logicalState = pinCfg->inverted ? !desiredState : desiredState;

        hardware->GPIO_Write(*pinCfg, logicalState ? GPIO_State::GPIO_HIGH : GPIO_State::GPIO_LOW );

        libCOL_numbered_output_t wrapper;
        wrapper.output = convertToOutput(mapping); // conversion function required
        wrapper.number = i;

        g_eventBus.output.notifyOutput(wrapper);
    outputNotificationFlag = true;
    }
}

void GPIOHandler::InterruptGPIOInputHandler() 
{
    while (!GPIOHandler::inputEventQueue.empty())
	{
        uint8_t index = GPIOHandler::inputEventQueue.front();
        GPIOHandler::inputEventQueue.pop();
        GPIOHandler::execSingleObserverInputPin(index); 
		
    }
}


void GPIOHandler::execSingleObserverInputPin(uint8_t index) 
{
    if (!_InputMap.isValid(index)) return;
    PinInfo* pinCfg = _InputMap.getGpio(index);
    const virtualIOMapping_data& mapping = _InputMap.getPinMapping(index);
    // _hardware->Delay(10); // Optional delay for debounce
    bool rawState = hardware->GPIO_Read(*pinCfg); // Read the raw state from hardware
    bool logicalState = pinCfg->inverted ? !rawState : rawState;

    bool stateChanged = hardware->updateDebounce(*pinCfg, logicalState);
    if (!stateChanged) return;
    // Notify the observers about the state change    
    
    // Step 1: Convert virtual mapping to libCOL_input_t
    libCOL_input_t input = convertToInput(mapping);

    // Step 2: Write updated state to OD
    input.functionData.raw = logicalState;
    //_hardware->Delay(50);
    help.writeInputMappingToOD(index, input);
    libCOL_numbered_input_t wrapper;
    wrapper.input = input;
    wrapper.number = index;

    g_eventBus.input.notifyInput(wrapper);
    input.functionData.raw = 0;
    help.writeInputMappingToOD(index, input);
    
}


bool GPIOHandler::isEqualExcludingData(const virtualIOMapping_data_t& a, const virtualIOMapping_data_t& b) 
{
    return a.basicFunction == b.basicFunction &&
           a.subFunction   == b.subFunction &&
           a.lift          == b.lift &&
           a.floor         == b.floor &&
           a.door          == b.door;
}

void GPIOHandler::onShiftRegisterInputChange(uint8_t index, bool logicalState) // Explain the steps here in a better way
{
    if (!_InputMap.isValid(index)) return;

    //PinInfo* pinCfg = _InputMap.getGpio(index);
    const virtualIOMapping_data& mapping = _InputMap.getPinMapping(index);

    // Step 1: Convert mapping to libCOL_input_t
    libCOL_input_t input = convertToInput(mapping);
    input.functionData.raw = logicalState;

    // Step 2: Write to OD
    help.writeInputMappingToOD(index, input);

    // Step 3: Notify input event bus
    libCOL_numbered_input_t wrapper;
    wrapper.input = input;
    wrapper.number = index;

    g_eventBus.input.notifyInput(wrapper);
}
