#include "STM32F0_Hardware.h"
#include "CANopen.h"
#include "core_cm0.h"
extern "C" 
{
    #include "CO_app_STM32.h"
}
#include "Hardware_Definitions.h"


//#define REGISTERIO

ActiveBoardPins boardPins; // The global instance for the selected board



STM32F0_Hardware* STM32F0_Hardware::s_instance = nullptr;




extern "C" void EXTI0_1_IRQHandler(void)
{

    if (!STM32F0_Hardware::s_instance) return;

    for (uint8_t pinLine = 0; pinLine <= 1; ++pinLine)

    {

        if (!STM32F0_Hardware::s_instance->extiEnabledPins[pinLine])
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

    if (!STM32F0_Hardware::s_instance) return;

    for (uint8_t pinLine = 2; pinLine <= 3; ++pinLine)
    {

        if (!STM32F0_Hardware::s_instance->extiEnabledPins[pinLine])
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

    if (!STM32F0_Hardware::s_instance) return;

    for (uint8_t pinLine = 4; pinLine <= 15; ++pinLine)

    {

        if (!STM32F0_Hardware::s_instance->extiEnabledPins[pinLine])
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
		if(STM32F0_Hardware::s_instance)
        {
            // Call the time handler of CANopenNode
            STM32F0_Hardware::s_instance->timingHandler();
	    
        }
    }

extern "C" void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
	{
		if(STM32F0_Hardware::s_instance)
        {
             STM32F0_Hardware::s_instance->timingHandler();
        }

	}

extern "C" void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan)
	{
		if(STM32F0_Hardware::s_instance)
		{
			//test
             STM32F0_Hardware::s_instance->timingHandler();
		}
	}

	//Callback for CAN Error
extern "C" void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
	{
		
        if (STM32F0_Hardware::s_instance)
        {
        
            STM32F0_Hardware::s_instance->errorHandler();
        
        }
		
	}

// A static/global pointer to our hardware instance:

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) 
    {

        if (STM32F0_Hardware::s_instance) 
        {
        
            STM32F0_Hardware::s_instance->HandlePinInterrupt(GPIO_Pin);
        
        }

    }


// end

int STM32F0_Hardware::CANopen_Init() 

{
    // Initialize the CANopenNode with the desired settings

   return canopen_app_init(&canopenNodeSTM32); // Pass the appropriate parameter if needed
   
}



void STM32F0_Hardware::CANopen_Process() 
{
    // Process the CANopenNode tasks

   canopen_app_process();
   
}

uint32_t STM32F0_Hardware::CANopen_Reset() 
{
    // Reset the CANopenNode state
    return canopen_app_resetCommunication();
}
void STM32F0_Hardware::CANopen_Interrupt() 
{
    // Handle the CANopenNode interrupt
    canopen_app_interrupt();
}




bool STM32F0_Hardware::isIdValid() 
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


void STM32F0_Hardware::getstate(int state)
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

void STM32F0_Hardware::timingHandler()
{
    if (nodestate)
    {
        canopen_app_interrupt();
    }

}


STM32F0_Hardware::STM32F0_Hardware() 
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


void STM32F0_Hardware::Init()
{
	

    // Register global instance for EXTI callback
    s_instance = this;
}

// Clock
void STM32F0_Hardware::Clock_Init() 
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

void STM32F0_Hardware::Delay(uint32_t ms) 
{

    HAL_Delay(ms);

}

uint32_t STM32F0_Hardware::GetTick() 

{

    return HAL_GetTick();

}

void STM32F0_Hardware::HandlePinInterrupt(uint16_t pinMask) 
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

void STM32F0_Hardware::ConfigureEXTIInterrupt(const PinInfo& pinCfg) 
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

    SYSCFG->EXTICR[extiRegIndex] &= ~(0xF << extiBitShift);
    SYSCFG->EXTICR[extiRegIndex] |= (portCode << extiBitShift);

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
void STM32F0_Hardware::GPIO_SetMode(void* port, uint8_t pin, GPIO_Mode mode) 
{

    GPIO_InitTypeDef gpio = {0};
    gpio.Pin = 1 << pin;
    gpio.Mode = static_cast<uint32_t>(mode);
    HAL_GPIO_Init(reinterpret_cast<GPIO_TypeDef*>(port), &gpio);

}

bool STM32F0_Hardware::GPIO_Read(const PinInfo& pin) 
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



void STM32F0_Hardware::GPIO_Write(const PinInfo& pin, GPIO_State state) 
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

void STM32F0_Hardware::GreenLed(bool state)
{
    //    GPIO_TypeDef *GPIOx = LED_GREEN_PORT;
    //     uint16_t pin = LED_GREEN_PIN;
   
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,state == GPIO_HIGH ? GPIO_PIN_SET : GPIO_PIN_RESET);

}
void  STM32F0_Hardware::RedLed() 
{


}
void STM32F0_Hardware::setpinDirection(int clamp, bool output)
{
  //Deprecated function To be Deleted
}

bool STM32F0_Hardware::GPIOPinInput(int clamp)
{   
    // Deprecated function To be Deleted
    // uint16_t pinLow = pins.getClampPin(clamp, false);
    // GPIO_TypeDef *GPIOx = pins.getClampGPIOPort(clamp);
    // return !(HAL_GPIO_ReadPin(GPIOx, pinLow) == pins.getClampInverted(clamp, false));
}

void STM32F0_Hardware::GPIOPinOutput(int clamp, bool state)
{
    // Deprecated function To be Deleted
    // uint16_t pinHigh = pins.getClampPin(clamp, true);
    // GPIO_TypeDef *GPIOx = pins.getClampGPIOPort(clamp);
    // HAL_GPIO_WritePin(GPIOx, pinHigh, (GPIO_PinState)(!(state == pins.getClampInverted(clamp, true))));
}

PinInfo STM32F0_Hardware::returnPinInput(int clamp) 
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

bool STM32F0_Hardware::updateDebounce(PinInfo& pinCfg, bool newState) 
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
PinInfo STM32F0_Hardware::returnPinOutput(int clamp) 
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

void STM32F0_Hardware::toggle(void* port, uint16_t pin) 
{
    GPIO_PinState currentState = HAL_GPIO_ReadPin(reinterpret_cast<GPIO_TypeDef*>(port), pin);
    GPIO_PinState newState = (currentState == GPIO_PIN_SET) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef*>(port), pin, newState);
}

// CAN
void STM32F0_Hardware::CAN_Init(uint8_t bus, uint32_t baudrate) 
{

}


void STM32F0_Hardware::CAN_Send(uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) 
{
    // ...implementation...
}

bool STM32F0_Hardware::CAN_Receive(uint8_t bus, uint32_t& id, uint8_t* buffer, uint8_t& len) 
{
    // ...implementation...
    return false;
}

void STM32F0_Hardware::CAN_ConfigFilter(uint8_t bus, uint32_t id, uint32_t mask) 
{
    // ...implementation...
}

void STM32F0_Hardware::errorHandler() 
{
    if(canopenNodeSTM32.CANHandle->ErrorCode != HAL_CAN_ERROR_NONE)
		{
			switch(canopenNodeSTM32.CANHandle->ErrorCode)
			{

			case HAL_CAN_ERROR_EWG:
			case HAL_CAN_ERROR_EPV:
			case HAL_CAN_ERROR_BOF:
			case HAL_CAN_ERROR_STF:
			case HAL_CAN_ERROR_FOR:
			case HAL_CAN_ERROR_ACK:
			case HAL_CAN_ERROR_BR:
			case HAL_CAN_ERROR_BD:
			case HAL_CAN_ERROR_CRC:
			case HAL_CAN_ERROR_RX_FOV0:
			case HAL_CAN_ERROR_RX_FOV1:
			case HAL_CAN_ERROR_TX_ALST0:
			case HAL_CAN_ERROR_TX_TERR0:
			case HAL_CAN_ERROR_TX_ALST1:
			case HAL_CAN_ERROR_TX_TERR1:
			case HAL_CAN_ERROR_TX_ALST2:
			case HAL_CAN_ERROR_TX_TERR2:
			case HAL_CAN_ERROR_TIMEOUT:
			case HAL_CAN_ERROR_NOT_INITIALIZED:
			case HAL_CAN_ERROR_NOT_READY:
			case HAL_CAN_ERROR_NOT_STARTED:
			case HAL_CAN_ERROR_PARAM:
			default:
				break;
			
            }

			//todo
			//canopen_app_resetCommunication();
		}
}

void STM32F0_Hardware::setHandles(int nodeId) 
{
    // Set hardware handles for CANopenNode
    const HardwareHandles* handles  = hwDefs.GetHardwareHandles();
    assert(handles != nullptr);
    assert(canopenNodeSTM32 != nullptr);
    
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
void STM32F0_Hardware::TFT_Init(uint16_t width, uint16_t height) 
{
    // ...implementation...
}

void STM32F0_Hardware::TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) 
{
    // ...implementation...
}

void STM32F0_Hardware::TFT_FillScreen(uint16_t color) 
{
    // ...implementation...
}

bool STM32F0_Hardware::TFT_TouchGetXY(uint16_t& x, uint16_t& y) 
{
    // ...implementation...
    return false;
}

// ADC
void STM32F0_Hardware::ADC_Start(uint8_t channel) 
{
//    hadc.Instance = ADC1;
//    hadc.Init.Resolution = ADC_RESOLUTION_12B;
//    HAL_ADC_Init(&hadc);
//    HAL_ADC_Start(&hadc);
}

uint16_t STM32F0_Hardware::ADC_Read(uint8_t channel) 
{
//    return HAL_ADC_GetValue(&hadc);
    return 0;
}

// PWM
void STM32F0_Hardware::PWM_Set(uint8_t timer, uint8_t channel, uint16_t value) 
{
    // ...implementation...
}

// Multi-core
void STM32F0_Hardware::M4_Core_Start(void (*func)(void)) 
{
    // ...implementation...
}

void STM32F0_Hardware::A7_Core_Init() 
{
    // ...implementation...
}

// Timer
void STM32F0_Hardware::Timer_Base_Start_IT(void* htim) 
{
    HAL_TIM_Base_Start_IT(reinterpret_cast<TIM_HandleTypeDef*>(htim));
}

// NVIC
void STM32F0_Hardware::System_Reset() 
{
    HAL_NVIC_SystemReset();
}

// Wireless (WB/WL)
#ifdef ENABLE_WIRELESS
void STM32F0_Hardware::BLE_Init() 
{
    // ...implementation...
}

void STM32F0_Hardware::LoRa_Send(uint8_t* data, uint8_t len) 
{
    // ...implementation...
}
#endif

// void STM32F0_Hardware::pollShiftRegisterInputs() {
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

void STM32F0_Hardware::pollShiftRegisterInputs() 
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


void STM32F0_Hardware::LEDblink(bool state) 
{
        //HAL_GPIO_WritePin(LED_GREEN_PORT ,LED_GREEN_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
        //allPins[0]->write(state); // Use the GreenLed function to control the LED state
        boardPins.GreenLED.write(state);
}

void STM32F0_Hardware::initAllPins() 
{
    for (auto pin : boardPins.allPins) pin->init();
}

