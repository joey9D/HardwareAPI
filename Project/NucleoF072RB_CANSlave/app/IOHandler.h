/*
 * IOHandler.h
 *
 *  Created on: Dec 18, 2023
 *      Author: michael.grathwohl
 * 
 * Changed by KS
 */

#ifndef IOHANDLER_H_
#define IOHANDLER_H_

#include <stdint.h>
#include <assert.h>
#include "../basic/Timer.h"
#include "main.h"
#include "Hardware_Factory_STM32.h" // Include the hardware factory header
#include "301/CO_ODinterface.h"
#include "OD.h"
#include "OD_Functions.h"
#include "../basic/singleton.h"
#include "CiA417_LiftTypes.h"
#include "CO_app_STM32.h"

#include "CANopenNode.h"






//#include "Hardware_Abstraction/STM32/STM32CANHardware.h"
// Global instance of hardware abstraction

//extern STM32CANHardware hardware;


class IOHandler {
	SINGLETON_DECLARE(IOHandler)
	

	public:
		// INPUTS

		

		void initNumberedInputsFromOD(const uint16_t inputCountMax,   libCOL_numbered_input_t* const inputs, libCOL_inputAcknowledge_t acknowledge);
		
	
		libCOL_numbered_input_t* getNumberedInputs();
		uint16_t getInputCount();
		void inputTriggerIndex(const uint16_t inputIndex);
		bool inputCompareIndex(const uint16_t inputIndex);
		bool inputCompare(const libCOL_input_t* input);
		void inputUpdateStatusIndex(const uint16_t inputIndex);
		void inputTrigger(const libCOL_input_t* input);
		bool inputEnabledIndex(const uint16_t inputIndex);
		static void CANopenInputAcknowledge(const libCOL_input_t* input);

		/*Helper Functions*/
		void loadAdjustments();
		void loadInputs();
		void getConfiguration();
		static uint16_t getFlashInterval(libCOL_outputFunctionData_t functionData); 		
		static uint16_t getPulseInterval(libCOL_outputFunctionData_t functionData); 
		void setupConfigCallbacks();
		void resetIO();
		void initLEDs();

		// OUTPUTS
		typedef void (*libCOL_outputCallback_t)(const libCOL_output_t* output);
		static libCOL_outputCallback_t libCOL_outputCallback;

		void initNumberedOutputsFromOD(const uint16_t outputCountMax,  libCOL_numbered_output_t* const outputs, libCOL_outputCallback_t callback);

		libCOL_numbered_output_t* getNumberedOutputs();
		uint16_t getOutputCount();
		void outputUpdateStatusIndexManual(const uint16_t outputIndex, bool indication);
		bool outputEnabledIndex(const uint16_t outputIndex);
		static void CANopenOutputCallback(const libCOL_output_t* output); 
		void loadOutputs();

		void loadClamps();

		// MAIN FUNCTIONS
		void initializeIO();
		void libCOL_process();
		void ProcessIO();
		void readInputs(uint32_t timerCount1ms);
		void checkIOSwitch(uint32_t timerCount1ms); 
		void checkOutputRefresh(uint32_t timerCount1ms); 
		void checkInputTransmission(uint32_t timerCount1ms);


	
	private:
		static ODR_t outputPDOCallback(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten);
		HardwareInterface* _hardware;
		CANopenNodeSTM32 _canOpenNodeParameter;
		bool _oldState = true;


	};	

/**
  @brief
    Local data for an virtual input.

    Contains configuration data.

  @ingroup cs08_io
    */
   typedef struct virtual_input_tag {
    /**
     * Virtual input number.
     */
    uint8_t number;
    /**
     * Pointer to the CANopenLift library object for the virtual input.
     */
    libCOL_input_t* input;
    /**
     * If input has been configured to be negated.
     */
    bool negated;
    } virtual_input_t;
    
    /**
          @brief
            Local data for an virtual output.
    
            Contains configuration, state and timer data.
    
          @ingroup cs08_io
        */
	typedef struct flash_state_tag {
		bool enabled;
		bool state;
		uint16_t interval;
		uint32_t flashChangeLast;
	} flash_state_t;

	typedef struct pulse_state_tag {
		bool enabled;
		bool state;
		uint16_t interval;
		uint32_t pulseChangeLast;
	} pulse_state_t;

	   typedef struct virtual_output_tag {
		/**
		 * Virtual output number.
		 */
		uint8_t number;
		/**
		 * Pointer to the CANopenLift library object for the virtual output.
		 */
		libCOL_output_t* output;
		/**
		 * Last applied function data.
		 */
		libCOL_outputFunctionData_t lastFunctionData;
		/**
		 * Last applied sub function data.
		 */
		uint8_t lastSubFunctionData;
		/**
		 * Next sub function data to be applied.
		 */
		uint8_t nextSubFunctionData;
		/**
		 * State of flashing property.
		 */
		flash_state_t flashState;
		/**
		 * State of pulsed property.
		 */
		pulse_state_t pulseState;
		/**
		 * Default state of flashing property.
		 */
		flash_state_t defaultFlashState;
		/**
		 * Default state of pulsed property.
		 */
		pulse_state_t defaultPulseState;
		/**
		 * If output has been configured to be negated.
		 */
		bool negated;
		/***
		 * If pulse is suppressed
		 */
		bool pulseSuppressed;
	} virtual_output_t;


class GPIOBasic
{
public:

	GPIOBasic(uint16_t Pin, GPIO_TypeDef* Port, bool inverted = false)
	{
		assert(Port != NULL);

		_Pin = Pin;
		_Port = Port;
		_invertedPin = inverted;
	};

	virtual ~GPIOBasic()
	{};

	uint16_t getPin()
	{
		return _Pin;
	};

	GPIO_TypeDef* getPort()
	{
		return _Port;
	};

	bool isPinInverted()
	{
		return _invertedPin;
	};

private:

	uint16_t _Pin = 0;
	GPIO_TypeDef* _Port = nullptr;
	bool _invertedPin = false;
};

class GPIOInput : public GPIOBasic
{
public:

	GPIOInput(uint16_t Pin, GPIO_TypeDef* Port, bool inverted, uint32_t debounceTime = 0) : GPIOBasic(Pin, Port, inverted)
	{
		_debounceTime = debounceTime;
		_hardware = HardwareFactory::Create();
	};

	bool isPinOn()
	{
		bool retval = false;
//
//		//if(HAL_GPIO_ReadPin(getPort(), getPin()) == GPIO_PIN_SET)
//	    // Use the abstraction layer to read the pin state
		if (_hardware->GPIO_Read(getPort(), static_cast<uint16_t>(getPin())) == GPIO_PIN_SET)
		{
			retval = true;

          // Use hardware interface object
		}
		if(isPinInverted())
		{
			retval = !retval;
		}
		return retval;
	};

	bool isDebouncePinOn()
	{
		bool retval = false;

		if(_debounceTime != 0)
		{
			switch(_debounceState)
			{
			case 0://pin off idle
				if(isPinOn())
				{
					_debounceTimer.startTime(_debounceTime);
					_debounceState = 1;//pin off debounce
				}
				break;
			case 1://pin off debounce
				if(isPinOn())
				{
					if(_debounceTimer.isTimeExpired())
					{
						_debounceState = 2;
					}
				}
				else
				{
					_debounceTimer.stopTime();
					_debounceState = 0;//pin off idle
				}
				break;
			case 2://pin on idle
				retval = true;
				if(!isPinOn())
				{
					_debounceTimer.startTime(_debounceTime);
					_debounceState = 3;//pin on debounce
				}
				break;
			case 3://pin on debounce
				retval = true;
				if(!isPinOn())
				{
					if(_debounceTimer.isTimeExpired())
					{
						_debounceState = 0;//pin off idle
					}
				}
				else
				{
					_debounceTimer.stopTime();
					_debounceState = 2;//pin on idle
				}
				break;
			default:
				_debounceState = 0;
				break;
			}
		}
		else
		{
			retval = isPinOn();
		}

		return retval;
	};

private:
	HardwareInterface* _hardware; // Hardware interface object

	uint32_t _debounceTime = 0;
	Timer _debounceTimer;
	uint8_t _debounceState = 0;
};

class GPIOOutput : public GPIOBasic
{
public:

	GPIOOutput(uint16_t Pin, GPIO_TypeDef* Port, bool inverted ) : GPIOBasic(Pin, Port, inverted)
	{
		_hardware = HardwareFactory::Create();
		setOutput(false);
	};

	void setOutput(bool onState)
	{
		if(_oldState != onState)
		{
//			GPIO_PinState PinState;
			_oldState = onState;
			// Applying Inversion Logic
//			bool outputValue =onState;
//			if(isPinInverted())
//			{
//	            outputValue = !outputValue;
//			}
//
//			hardware.GPIO_Write(getPin(), outputValue);

			 _hardware->GPIO_Write(getPort(), static_cast<uint8_t>(getPin()), onState ? GPIO_HIGH : GPIO_LOW); // Use hardware interface object

		}
	};

	void toggle()
	{
		setOutput(!_oldState);
	};

	bool isPinOn()
	{
		return _oldState;
	};

private:
	HardwareInterface* _hardware; // Hardware interface object
	bool _oldState = true;
};

/*Main IO Functions for Call in Main App*/





#endif /* IOHANDLER_H_ */
