#include "STM32G0_Hardware.h"
#include "CANopen.h"
extern "C" 
{
    #include "CO_app_STM32.h"
}
#include "Hardware_Definitions.h"


//#define REGISTERIO

ActiveBoardPins boardPins; // The global instance for the selected board



STM32G0_Hardware* STM32G0_Hardware::s_instance = nullptr;




extern "C" void EXTI0_1_IRQHandler(void)
{

    if (!STM32G0_Hardware::s_instance) return;

    for (uint8_t pinLine = 0; pinLine <= 1; ++pinLine)

    {

        if (!STM32G0_Hardware::s_instance->extiEnabledPins[pinLine])
            continue;

        uint16_t pin = 1 << pinLine;
        if (__HAL_GPIO_EXTI_GET_IT(pin) != RESET)
        {

            HAL_GPIO_EXTI_IRQHandler(pin);

        }

    }

}

extern "C" void EXTI2_3_IRQHandler(void)
{

    if (!STM32G0_Hardware::s_instance) return;

    for (uint8_t pinLine = 2; pinLine <= 3; ++pinLine)
    {

        if (!STM32G0_Hardware::s_instance->extiEnabledPins[pinLine])
            continue;

        uint16_t pin = 1 << pinLine;
        if (__HAL_GPIO_EXTI_GET_IT(pin) != RESET)
        {

            HAL_GPIO_EXTI_IRQHandler(pin);

        }

    }

}

extern "C" void EXTI4_15_IRQHandler(void)
{

    if (!STM32G0_Hardware::s_instance) return;

    for (uint8_t pinLine = 4; pinLine <= 15; ++pinLine)

    {

        if (!STM32G0_Hardware::s_instance->extiEnabledPins[pinLine])
            continue;

        uint16_t pin = 1 << pinLine;
        if (__HAL_GPIO_EXTI_GET_IT(pin) != RESET)
        {

            HAL_GPIO_EXTI_IRQHandler(pin);

        }

    }

}





extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
	{
		if(STM32G0_Hardware::s_instance)
        {
            // Call the time handler of CANopenNode
            STM32G0_Hardware::s_instance->timingHandler();
	    
        }
    }

//extern "C" void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs)
//	{
//		if(STM32G0_Hardware::s_instance)
//        {
//             STM32G0_Hardware::s_instance->timingHandler();
//        }
//
//	}
//
extern "C" void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo1ITs)
	{
		if (hfdcan == &hfdcan1 && (RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE))
		{
	        	while (HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO1) > 0)
	        	{
	        		FDCAN_RxHeaderTypeDef rxHeader;
	        		uint8_t rxData[8];
	        		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &rxHeader, rxData) == HAL_OK)
	        		{
	                // Check for CANopen bootup message: CAN-ID 0x701–0x77F, DLC=1, data[0]=0x00
	        			if ((rxHeader.Identifier & 0x780) == 0x700 &&
	        					rxHeader.DataLength == FDCAN_DLC_BYTES_1 &&
								rxData[0] == 0x00)
	        			{
	                    uint8_t nodeId = rxHeader.Identifier & 0x7F;
	                    // --- Handle bootup for nodeId here ---
	        			}
	        		}
	        	}
		}
        else 
        {
            if (RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE && STM32G0_Hardware::s_instance) 
            {
            // Read all messages in FIFO1
            while (HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO1) > 0) 
                {
                    FDCAN_RxHeaderTypeDef rxHeader;
                    uint8_t rxData[8];
                    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &rxHeader, rxData) == HAL_OK) 
                    {
                        // Call the registered CAN interrupt callback
                        if (STM32G0_Hardware::s_instance->m_canInterruptCallback) {
                            STM32G0_Hardware::s_instance->m_canInterruptCallback(rxData, rxHeader.Identifier);
                        }
                    }
                }
            }
        }

    }

	//Callback for CAN Error
extern "C" void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan)
	{

        if (STM32G0_Hardware::s_instance)
        {

            STM32G0_Hardware::s_instance->errorHandler();

        }
		
	}

// A static/global pointer to our hardware instance:

extern "C" void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
    {

        if (STM32G0_Hardware::s_instance) 
        {

            STM32G0_Hardware::s_instance->HandlePinInterrupt(GPIO_Pin);

        }

    }


// end

int STM32G0_Hardware::CANopen_Init() 

{
    // Initialize the CANopenNode with the desired settings
 
   return canopen_app_init(&canopenNodeSTM32); // Pass the appropriate parameter if needed
   
}



void STM32G0_Hardware::CANopen_Process() 
{
    // Process the CANopenNode tasks

   canopen_app_process();
   
}

uint32_t STM32G0_Hardware::CANopen_Reset() 
{
    // Reset the CANopenNode state
    return canopen_app_resetCommunication();
}
void STM32G0_Hardware::CANopen_Interrupt() 
{
    // Handle the CANopenNode interrupt
    canopen_app_interrupt();
}




bool STM32G0_Hardware::isIdValid() 
{
    if (canopenNodeSTM32.desiredNodeID!= canopenNodeSTM32.activeNodeID)
    {
        return false; // Node ID is not valid
    }

    else 
    {
        return true; // Node ID is valid
    }

}


void STM32G0_Hardware::getstate(int state)
{
    if (state ==0)
    {
         nodestate= false; // Node is not in the desired state
    }

    else
    {
        nodestate = true ; // Node is in the desired state
    }


}

void STM32G0_Hardware::MasterNodesendCommand(int command , int nodeId)
{
    // Default command is sent to all nodes (nodeId = 0)
    // Reset the master node
    CO_NMT_sendCommand(canopenNodeSTM32.canOpenStack->NMT, (CO_NMT_command_t)command, nodeId); // Send reset command to all nodes to hear bootup at correct time.
}

bool STM32G0_Hardware::getNMTinternalstate(int state)
{
    // Get NMT internal state
    if (CO_NMT_getInternalState(canopenNodeSTM32.canOpenStack->NMT) == state)
    {
        return true;
    }
    return false;
}
void STM32G0_Hardware::setNMTinternalstate(int state)
{
    // Set NMT internal state
    CO_NMT_sendInternalCommand(canopenNodeSTM32.canOpenStack->NMT, (CO_NMT_command_t)state);
}

void STM32G0_Hardware::RegisterMasterCallbacks() 
{
    // Register callbacks for master node events
    CO_HBconsumer_initCallbackNmtChanged(canopenNodeSTM32.canOpenStack->HBcons,0, this, onNodeNmtChanged);
    //CO_NMT_registerCallback(canopenNodeSTM32.canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, onNmtStateChange, &canopenNodeSTM32);
    //CO_HBconsumer_registerCallback(canopenNodeSTM32.canOpenStack->HBcons, onHeartbeatTimeout, &canopenNodeSTM32);
}
void STM32G0_Hardware::NodeStateHandler()
{

    CO_HBconsumer_t* hbCons = canopenNodeSTM32.canOpenStack->HBcons; // You may need to implement this getter

    if (!hbCons)
    {
        return;
    }

    //     for (uint8_t i = 0; i < hbCons->numberOfMonitoredNodes; ++i) 
    // {
    //     CO_HBconsNode_t* node = &hbCons->monitoredNodes[i];
    //     uint8_t nodeId = node->nodeId;

    //     // Detect transition from inactive to active
    //     if (node->HBstate == CO_HBconsumer_ACTIVE && node->NMTstate == CO_NMT_PRE_OPERATIONAL) 
    //     {
    //         // Node just became active
    //         CO_NMT_sendCommand(canopenNodeSTM32.canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, nodeId);
    //         // You may want to log this event or take other actions
    //         lastHBstate[nodeId] = node->HBstate; // Update last state
    //     }

    //     if (node->HBstate == CO_HBconsumer_ACTIVE && node->NMTstate == CO_NMT_OPERATIONAL) 
    //     {
    //         // Node is operational, update last state
    //         lastHBstate[nodeId] = node->HBstate;
    //     } 
    //     else if (node->HBstate == CO_HBconsumer_INACTIVE || node->HBstate == CO_HBconsumer_UNKNOWN) 
    //     {
    //         // Node is inactive or unknown, check if it was previously active
    //         if (lastHBstate[nodeId] == CO_HBconsumer_ACTIVE) 
    //         {
    //             // Node just became inactive or unknown
    //             // You may want to log this event or take other actions
    //             lastHBstate[nodeId] = node->HBstate; // Update last state
    //         }
    //     }
        
    // }
    // for (uint8_t i = 0; i < hbCons->numberOfMonitoredNodes; ++i) {
    //     CO_HBconsNode_t* node = &hbCons->monitoredNodes[i];
    //     uint8_t nodeId = node->nodeId;
    //     uint32_t now = HAL_GetTick();

    //     // If node booted up and is pre-operational, and not yet operational, send NMT operational ONCE
    //     if (node->HBstate == CO_HBconsumer_ACTIVE &&
    //         node->NMTstate == CO_NMT_PRE_OPERATIONAL &&
    //         nodeStatus[nodeId].bootup_received &&
    //         !nodeStatus[nodeId].operational)
    //     {
    //         if( now - nodeStatus[nodeId].lastNmtCommandTime > 1000) // Avoid spamming NMT command
    //         {
    //             CO_NMT_sendCommand(canopenNodeSTM32.canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, nodeId);
    //             nodeStatus[nodeId].lastNmtCommandTime = now; // Update last NMT command time
    //             // Don't set operational=true here; wait for confirmation via callback
    //         }
    //     }
    // }
       for (uint8_t i = 0; i < hbCons->numberOfMonitoredNodes; ++i) {
        CO_HBconsNode_t* node = &hbCons->monitoredNodes[i];
        uint8_t nodeId = node->nodeId;
        uint32_t now = HAL_GetTick();

        // If node booted up and is pre-operational, and not yet operational, send NMT operational ONCE
        if (node->HBstate == CO_HBconsumer_ACTIVE &&
            node->NMTstate == CO_NMT_PRE_OPERATIONAL &&
            !nodeStatus[nodeId].operational)
        {
            if( now - nodeStatus[nodeId].lastNmtCommandTime > 1000) // Avoid spamming NMT command
            {
                CO_NMT_sendCommand(canopenNodeSTM32.canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, nodeId);
                nodeStatus[nodeId].lastNmtCommandTime = now; // Update last NMT command time
                // Don't set operational=true here; wait for confirmation via callback
            }
        }
    }


}


void STM32G0_Hardware::onNodeNmtChanged(uint8_t nodeId, uint8_t idx, CO_NMT_internalState_t NMTstate, void *object)
{
    //CO_NMT_t *nmt = (CO_NMT_t *)object;

    // // Handle NMT state change
    // switch (NMTstate) 
    // {
    //     case CO_NMT_OPERATIONAL:
    //         {// Node entered operational state
    //         // You may want to log, enable outputs, etc.
    //         break;
    //         }
    //     case CO_NMT_PRE_OPERATIONAL:
    //         {// Node entered pre-operational state (e.g., after bootup)
    //         // If you want all nodes to be operational, send NMT operational command here:
    //         CO_NMT_sendCommand((CO_NMT_t*)object, CO_NMT_ENTER_OPERATIONAL, nodeId);
    //         break;
    //         }
    //     case CO_NMT_INITIALIZING:
    //         {// Node sent bootup message (CANopen bootup)
    //         // You may want to send NMT operational here as well
    //         CO_NMT_sendCommand((CO_NMT_t*)object, CO_NMT_ENTER_OPERATIONAL, nodeId);
    //         break;
    //         }
    //     case CO_NMT_UNKNOWN:
    //         {// Node is lost (timeout or not yet seen)
    //         // Handle node lost: log, alert, disable outputs, etc.
    //         CO_NMT_sendCommand((CO_NMT_t*)object, CO_NMT_ENTER_OPERATIONAL, nodeId);
    //         break;
    //         }
    //     case CO_NMT_STOPPED:
    //         {// Node entered stopped state
    //         // Optional: handle as needed
    //         break;
    //         }
    //     default:
    //         {// Other states if any
    //         break;
    //         }
    // }
    STM32G0_Hardware* hardware = static_cast<STM32G0_Hardware*>(object);
      if (nodeId >= 128) 
      {
          return;
      }

    switch (NMTstate) 
    {
        case CO_NMT_INITIALIZING:
        {
            hardware->nodeStatus[nodeId].bootup_received = true;
            hardware->nodeStatus[nodeId].operational = false;
            // Optionally send NMT operational here, or let NodeStateHandler do it
            break;
        }
        case CO_NMT_OPERATIONAL:
        {
            hardware->nodeStatus[nodeId].operational = true;
            break;
        }
        case CO_NMT_PRE_OPERATIONAL:
        {
            hardware->nodeStatus[nodeId].operational = false;
            break;
        }
        default:
        {
            hardware->nodeStatus[nodeId].operational = false;
            break;
        }
    }
}
bool STM32G0_Hardware::allNodesBooted() 
{
    for (uint8_t i = 0; i < MAX_NODES; ++i) 
    {
        if (nodeStatus[i].bootup_received && !nodeStatus[i].operational) 
        {
            return false; // At least one node is not operational
        }
    }
    return true; // All nodes are operational
}



void STM32G0_Hardware::timingHandler()
{
    if (nodestate)
    {
        canopen_app_interrupt();
    }

}


STM32G0_Hardware::STM32G0_Hardware() 
{
    // _shiftIO.init();
    initAllPins(); // Initialize all board pins
    for (uint8_t i = 0; i < 8; ++i) 
    {
    
        _shiftRegisterPins[i].virtualSource = VirtualPinSource::ShiftRegister;
        _shiftRegisterPins[i].virtualIndex = i;
        _shiftRegisterPins[i].debounceTime = 0; // ms
    
    }

}


void STM32G0_Hardware::Init()
{
	

    // Register global instance for EXTI callback
    s_instance = this;
}

// Clock
void STM32G0_Hardware::Clock_Init()
{
    RCC_OscInitTypeDef osc = {0};
    osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    HAL_RCC_OscConfig(&osc);

    RCC_ClkInitTypeDef clk = {0};
    clk.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0);
}

void STM32G0_Hardware::Delay(uint32_t ms)
{

    HAL_Delay(ms);

}

uint32_t STM32G0_Hardware::GetTick()

{

    return HAL_GetTick();

}

void STM32G0_Hardware::HandlePinInterrupt(uint16_t pinMask)
{

#ifdef REGISTERIO

    return; // No need to handle if not using shift register
#endif

   // Check if the pin is in the input map

	 uint8_t pinLine = __builtin_ctz(pinMask);
	    int8_t index = pinToIndexLUT[pinLine];

	    if (index >= 0 && m_pinInterruptCallback) 
        {
             m_pinInterruptCallback(index);
            //m_gpioHandler->inputEventQueue.push(index);
	    
        }
}

void STM32G0_Hardware::ConfigureEXTIInterrupt(const PinInfo& pinCfg) 
{   
    pinToIndexLUT.fill(-1); // -1 = unmapped; LUT refers to Lookup Table

    assert(pinCfg.id < boardPins.clampInputs.size());
    const Pin* pinObj = boardPins.clampInputs[pinCfg.id];

	GPIO_TypeDef* port = pinObj->port();
    uint16_t pin = pinObj->pin();
    uint8_t pinNumber = __builtin_ctz(pin);  // pin must be 1 << N (e.g., GPIO_PIN_13)
    extiEnabledPins[pinNumber] = true;

    // 1. Register EXTI line to logical index mapping
    pinToIndexLUT[pinNumber] = pinCfg.id;

    // 2. Map EXTI line to the correct GPIO port via SYSCFG
    uint8_t portCode = 0;
    if (port == GPIOA) portCode = 0;
    else if (port == GPIOB) portCode = 1;
    else if (port == GPIOC) portCode = 2;
    else if (port == GPIOD) portCode = 3;
    else if (port == GPIOF) portCode = 5;

    uint8_t extiRegIndex = pinNumber / 4;
    uint8_t extiBitShift = (pinNumber % 4) * 4;

    EXTI->EXTICR[extiRegIndex] &= ~(0xF << extiBitShift);
    EXTI->EXTICR[extiRegIndex] |= (portCode << extiBitShift);

    // 3. Clear pending flag and enable EXTI IRQ line
    __HAL_GPIO_EXTI_CLEAR_IT(pin);

    if (pinNumber <= 1)
        HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
    else if (pinNumber <= 3)
        HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);
    else
        HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

    // Set priority (optional, tune as needed)
    HAL_NVIC_SetPriority(EXTI4_15_IRQn, 2, 0);

}


// GPIO
void STM32G0_Hardware::GPIO_SetMode(void* port, uint8_t pin, GPIO_Mode mode) 
{

    GPIO_InitTypeDef gpio = {0};
    gpio.Pin = 1 << pin;
    gpio.Mode = static_cast<uint32_t>(mode);
    HAL_GPIO_Init(reinterpret_cast<GPIO_TypeDef*>(port), &gpio);

}

bool STM32G0_Hardware::GPIO_Read(const PinInfo& pin) 
{   
    assert(pin.id < boardPins.clampInputs.size());

    const Pin* pininfo = boardPins.clampInputs[pin.id];
	#ifdef REGISTERIO
		if (pin.virtualSource == VirtualPinSource::ShiftRegister) 
        
        {
		
            return _shiftIO.getInputBit(pin.virtualIndex);  // Use correct index
		
        }
	#endif

    //GPIO_PinState rawState = HAL_GPIO_ReadPin(reinterpret_cast<GPIO_TypeDef*>(pin.port), pin.pin);

    // Apply inversion logic if the pin is inverted
    return pininfo->read(); // Read the pin state using the Pin class method
}



void STM32G0_Hardware::GPIO_Write(const PinInfo& pin, GPIO_State state) 
{
    assert(pin.id < boardPins.clampOutputs.size());

    #ifdef REGISTERIO
		if (pin.virtualSource == VirtualPinSource::ShiftRegister) 
        {
			_shiftIO.setOutputBit(pin.virtualIndex, state);  // Use correct index
			return;
		}
	#endif
    Pin* pininfo = boardPins.clampOutputs[pin.id];

    pininfo->write(state); // Write the pin state using the Pin class method
}

void STM32G0_Hardware::GreenLed(bool state)
{
    //    GPIO_TypeDef *GPIOx = LED_GREEN_PORT;
    //     uint16_t pin = LED_GREEN_PIN;
   
    //HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,state == GPIO_HIGH ? GPIO_PIN_SET : GPIO_PIN_RESET);

}
void  STM32G0_Hardware::RedLed() 
{


}
void STM32G0_Hardware::setpinDirection(int clamp, bool output)
{
  //Deprecated function To be Deleted
}

bool STM32G0_Hardware::GPIOPinInput(int clamp)
{   
    // Deprecated function To be Deleted
    // uint16_t pinLow = pins.getClampPin(clamp, false);
    // GPIO_TypeDef *GPIOx = pins.getClampGPIOPort(clamp);
    // return !(HAL_GPIO_ReadPin(GPIOx, pinLow) == pins.getClampInverted(clamp, false));
}

void STM32G0_Hardware::GPIOPinOutput(int clamp, bool state)
{
    // Deprecated function To be Deleted
    // uint16_t pinHigh = pins.getClampPin(clamp, true);
    // GPIO_TypeDef *GPIOx = pins.getClampGPIOPort(clamp);
    // HAL_GPIO_WritePin(GPIOx, pinHigh, (GPIO_PinState)(!(state == pins.getClampInverted(clamp, true))));
}

PinInfo STM32G0_Hardware::returnPinInput(int clamp) 
{
    assert(clamp >= 0 && clamp < boardPins.clampInputs.size());
    PinInfo info;

    #ifdef REGISTERIO
    
        info.virtualSource = VirtualPinSource::ShiftRegister;
        info.virtualIndex = clamp;
        return info;
    
    #endif

    info.id = clamp; // Unique ID for the pin
    info.inverted = boardPins.clampInputs[clamp]->inverted();
    info.debounceTime = 300;
    return info;
}

namespace 
{
    constexpr uint8_t MaxPins = 1; // Adjust if needed
    std::array<uint32_t, MaxPins> lastChangeTime = {0};
    std::array<bool, MaxPins> lastState = {false};
}

bool STM32G0_Hardware::updateDebounce(PinInfo& pinCfg, bool newState) 
{
    
    static constexpr uint8_t RISING_ONLY = 1;

    uint32_t now = HAL_GetTick();
    bool stateChanged = false;

    if (newState) 
    {  // Rising edge detected
        if ((now - pinCfg.lastDebounceTime) >= static_cast<uint32_t>(pinCfg.debounceTime)) 
        {
            pinCfg.lastDebounceTime = now;
            stateChanged = true;  // Valid rising event
        }
        // else: too soon — debounce in effect
    }

    return stateChanged;
}

// For output pins:
PinInfo STM32G0_Hardware::returnPinOutput(int clamp) 
{
    assert(clamp >= 0 && clamp < boardPins.clampOutputs.size());
    PinInfo info;


    #ifdef REGISTERIO
        info.virtualSource = VirtualPinSource::ShiftRegister;
        info.virtualIndex = clamp;
        return info;
    
    #endif

    info.id = clamp; // Use clamp as the index
    info.inverted = boardPins.clampOutputs[clamp]->inverted();
    info.debounceTime = 300;
    return info;

}

void STM32G0_Hardware::toggle(void* port, uint16_t pin) // Not in use to be deleted
{
    GPIO_PinState currentState = HAL_GPIO_ReadPin(reinterpret_cast<GPIO_TypeDef*>(port), pin);
    GPIO_PinState newState = (currentState == GPIO_PIN_SET) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef*>(port), pin, newState);
}

// CAN
void STM32G0_Hardware::CAN_Init(uint8_t bus, uint32_t baudrate) 
{

}


void STM32G0_Hardware::CAN_Send(uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) 
{
    // ...implementation...
}

bool STM32G0_Hardware::CAN_Receive(uint8_t bus, uint32_t& id, uint8_t* buffer, uint8_t& len) 
{
    // ...implementation...
    return false;
}

void STM32G0_Hardware::CAN_ConfigFilter(uint8_t bus, uint32_t id, uint32_t mask) 
{
    // ...implementation...
}

void STM32G0_Hardware::errorHandler() 
{
    if(canopenNodeSTM32.CANHandle->ErrorCode != HAL_FDCAN_ERROR_NONE)
		{
			switch(canopenNodeSTM32.CANHandle->ErrorCode)
			{

			case HAL_FDCAN_ERROR_TIMEOUT:
			case HAL_FDCAN_ERROR_NOT_INITIALIZED:
			case HAL_FDCAN_ERROR_NOT_READY:
			case HAL_FDCAN_ERROR_NOT_STARTED:
			case HAL_FDCAN_ERROR_NOT_SUPPORTED:
			case HAL_FDCAN_ERROR_PARAM:
			case HAL_FDCAN_ERROR_PENDING:
			case HAL_FDCAN_ERROR_RAM_ACCESS:
			case HAL_FDCAN_ERROR_FIFO_EMPTY:
			case HAL_FDCAN_ERROR_FIFO_FULL:
			case HAL_FDCAN_ERROR_LOG_OVERFLOW:
			case HAL_FDCAN_ERROR_RAM_WDG:
			case HAL_FDCAN_ERROR_PROTOCOL_ARBT:
			case HAL_FDCAN_ERROR_PROTOCOL_DATA:
			case HAL_FDCAN_ERROR_RESERVED_AREA:
			default:
				break;
			
            }

			//todo
			//canopen_app_resetCommunication();
		}
}

void STM32G0_Hardware::setHandles(int nodeId) 
{
    // Set hardware handles for CANopenNode
    const HardwareHandles* handles  = hwDefs.GetHardwareHandles();
    assert(handles != nullptr);
    //assert(canopenNodeSTM32 != nullptr);
    
    canopenNodeSTM32.CANHandle = handles->can; // Assuming hcan1 is defined elsewhere
    canopenNodeSTM32.timerHandle = handles->timer; // Assuming htim3 is defined elsewhere
    canopenNodeSTM32.HWInitFunction = handles->canInitFunc; // Assuming MX_CAN_Init is defined elsewhere
    canopenNodeSTM32.desiredNodeID = nodeId;
	canopenNodeSTM32.activeNodeID = 0;
	canopenNodeSTM32.baudrate = 250;
	canopenNodeSTM32.timerCall_in_us = DEFAULT_CAN_TIMERIRQ_IN_US;
	canopenNodeSTM32.outStatusLEDGreen = 0;
	canopenNodeSTM32.outStatusLEDRed = 0;
	canopenNodeSTM32.canOpenStack = nullptr;
    assert(canopenNodeSTM32.CANHandle != nullptr);
    assert(canopenNodeSTM32.timerHandle != nullptr);
    assert(canopenNodeSTM32.HWInitFunction != nullptr);


}

// TFT/Display
void STM32G0_Hardware::TFT_Init(uint16_t width, uint16_t height) 
{
    // ...implementation...
}

void STM32G0_Hardware::TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) 
{
    // ...implementation...
}

void STM32G0_Hardware::TFT_FillScreen(uint16_t color) 
{
    // ...implementation...
}

bool STM32G0_Hardware::TFT_TouchGetXY(uint16_t& x, uint16_t& y) 
{
    // ...implementation...
    return false;
}

// ADC
void STM32G0_Hardware::ADC_Start(uint8_t channel) 
{
//    hadc.Instance = ADC1;
//    hadc.Init.Resolution = ADC_RESOLUTION_12B;
//    HAL_ADC_Init(&hadc);
//    HAL_ADC_Start(&hadc);
}

uint16_t STM32G0_Hardware::ADC_Read(uint8_t channel) 
{
//    return HAL_ADC_GetValue(&hadc);
    return 0;
}

// PWM
void STM32G0_Hardware::PWM_Set(uint8_t timer, uint8_t channel, uint16_t value) 
{
    // ...implementation...
}

// Multi-core
void STM32G0_Hardware::M4_Core_Start(void (*func)(void)) 
{
    // ...implementation...
}

void STM32G0_Hardware::A7_Core_Init() 
{
    // ...implementation...
}

// Timer
void STM32G0_Hardware::Timer_Base_Start_IT(void* htim) 
{
    HAL_TIM_Base_Start_IT(reinterpret_cast<TIM_HandleTypeDef*>(htim));
}

// NVIC
void STM32G0_Hardware::System_Reset() 
{
    HAL_NVIC_SystemReset();
}

// Wireless (WB/WL)
#ifdef ENABLE_WIRELESS
void STM32G0_Hardware::BLE_Init() 
{
    // ...implementation...
}

void STM32G0_Hardware::LoRa_Send(uint8_t* data, uint8_t len) 
{
    // ...implementation...
}
#endif

// void STM32G0_Hardware::pollShiftRegisterInputs() {
//      #ifdef REGISTERIO
//          uint8_t current = _shiftIO.readInputs();

//          for (uint8_t i = 0; i < 8; ++i) {
//              bool currentBit = (current >> i) & 0x01;
//              bool previousBit = (_lastShiftInputState >> i) & 0x01;
//              if (currentBit != previousBit) {
//                  m_gpioHandler->inputEventQueue.push(i-1);
//              }
//          }
//          _lastShiftInputState = current;
//      #endif
//     }

int  STM32G0_Hardware::initandSetFilters(const std::array<uint32_t,13>& arr)  ///< Register CAN ID filters
{
    int err = 0;
    // Initialize FDCAN1
    hwDefs.MX_FDCAN2_Init(250);
    // Register the FDCAN2 filters
    if (Register_FDCAN_ExtendedID_Filters(&hfdcan2, arr,  1) != HAL_OK) // 1 = RXFIFO1OK;
    {
        err = -1;
        return err; // Error in filter registration
    }
    if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK) // Enable RX FIFO 1 notification
    {
        err = -1;
        return err; // Error in activating notification
    }

    // Start FDCAN2
    if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK) 
    {
        err = -1;
        return err; // Error in starting FDCAN
    }

    return err; // Success
    
}


void STM32G0_Hardware::CANerrorHandler() 
{
    if(hfdcan2.ErrorCode != HAL_FDCAN_ERROR_NONE)
		{
			switch(hfdcan2.ErrorCode)
			{

			case HAL_FDCAN_ERROR_TIMEOUT:
			case HAL_FDCAN_ERROR_NOT_INITIALIZED:
			case HAL_FDCAN_ERROR_NOT_READY:
			case HAL_FDCAN_ERROR_NOT_STARTED:
			case HAL_FDCAN_ERROR_NOT_SUPPORTED:
			case HAL_FDCAN_ERROR_PARAM:
			case HAL_FDCAN_ERROR_PENDING:
			case HAL_FDCAN_ERROR_RAM_ACCESS:
			case HAL_FDCAN_ERROR_FIFO_EMPTY:
			case HAL_FDCAN_ERROR_FIFO_FULL:
			case HAL_FDCAN_ERROR_LOG_OVERFLOW:
			case HAL_FDCAN_ERROR_RAM_WDG:
			case HAL_FDCAN_ERROR_PROTOCOL_ARBT:
			case HAL_FDCAN_ERROR_PROTOCOL_DATA:
			case HAL_FDCAN_ERROR_RESERVED_AREA:
			default:
				break;
			
            }
            // Simple error handling: stop and restart the FDCAN2 interface
            // HAL_FDCAN_Stop(&hfdcan2);
            // HAL_FDCAN_Start(&hfdcan2);

		}
}

void STM32G0_Hardware::RegisterCANInterruptCallback(CANInterruptCallback cb) 
{
    m_canInterruptCallback = cb;
}

void STM32G0_Hardware::pollShiftRegisterInputs() 
{
    #ifdef REGISTERIO
        uint8_t current = _shiftIO.readInputs();
//    	static bool toggle = false;
//    	uint8_t current = toggle ? (1 << 2) : 0x00;
//    	toggle = !toggle;
        for (uint8_t i = 0; i < 8; ++i) 
        {
            bool currentBit = (current >> i) & 0x01;
            bool previousBit = (_lastShiftInputState >> i) & 0x01;
    
            if (currentBit != previousBit) 
            {
                if (updateDebounce(_shiftRegisterPins[i], currentBit)) 
                {
                    //m_gpioHandler->onShiftRegisterInputChange(i-1, currentBit);
                    if (m_pinInterruptCallback) m_pinInterruptCallback(i);

                }
            }
        }
        _lastShiftInputState = current;
    #endif
}


void STM32G0_Hardware::LEDblink(bool state) 
{
        //HAL_GPIO_WritePin(LED_GREEN_PORT ,LED_GREEN_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
        //allPins[0]->write(state); // Use the GreenLed function to control the LED state
        boardPins.GreenLED.write(state);
}

void STM32G0_Hardware::initAllPins() 
{
    for (auto pin : boardPins.allPins) pin->init();
}

// Project Specific Functions
template <size_t N>
HAL_StatusTypeDef STM32G0_Hardware::Register_FDCAN_ExtendedID_Filters(FDCAN_HandleTypeDef *hfdcan,
                                                    const std::array<uint32_t, N>& ext_ids,
                                                    uint32_t fifo_num)
{
   for (uint32_t i = 0; i < ext_ids.size(); i += 2) {
       FDCAN_FilterTypeDef sFilterConfig = {0};
       sFilterConfig.IdType = FDCAN_EXTENDED_ID;
       sFilterConfig.FilterIndex = i / 2;
       sFilterConfig.FilterType = FDCAN_FILTER_DUAL;
       sFilterConfig.FilterConfig = (fifo_num == 1) ? FDCAN_FILTER_TO_RXFIFO1 : FDCAN_FILTER_TO_RXFIFO0;
       sFilterConfig.FilterID1 = ext_ids[i];
       sFilterConfig.FilterID2 = (i+1 < ext_ids.size()) ? ext_ids[i+1] : 0;

       HAL_StatusTypeDef ret = HAL_FDCAN_ConfigFilter(hfdcan, &sFilterConfig);
       if (ret != HAL_OK) {
           // Optional: print which ID failed, or handle error
           return ret;
       }
   }
   return HAL_OK;
}
