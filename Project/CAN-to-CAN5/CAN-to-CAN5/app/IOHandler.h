/*
 * IOHandler.h
 *
 *  Created on: Dec 18, 2023
 *      Author: michael.grathwohl
 * 
 * Changed by KS
 */

 /* !!!!!!!!!!!!!!!!!!! Class to be deleted only used for testing*/


#ifndef IOHANDLER_H_
#define IOHANDLER_H_

#include <stdint.h>
#include <assert.h>
#include "../basic/Timer.h"
#include "main.h"
#include "Hardware_Factory.h" // Include the hardware factory header
#include "301/CO_ODinterface.h"
#include "OD.h"
#include "../basic/singleton.h"
#include "CiA417_LiftTypes.h"


#include "CANopenNode.h"






//#include "Hardware_Abstraction/STM32/STM32CANHardware.h"
// Global instance of hardware abstraction

//extern STM32CANHardware hardware;


class IOHandler 
{
	

	public:
		// INPUTS

		

//		void initNumberedInputsFromOD(const uint16_t inputCountMax,   libCOL_numbered_input_t* const inputs, libCOL_inputAcknowledge_t acknowledge);
		
	
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


#endif /* IOHANDLER_H_ */
