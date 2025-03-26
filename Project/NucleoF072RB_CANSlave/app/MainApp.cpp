/*
 * MainApp.cpp
 *
 *  Created on: Dec 6, 2023
 *      Author: michael.grathwohl
 */

#include "MainApp.h"
#include "globals.h"
#include "CANopenNode.h"
//#include "CiA417_LiftTypes.h"
//#include "VirtualIOMapping.h"

#include "../basic/Timer.h"
#include <chrono>
#include "OD.h"
#include "IOHandler.h"

//static virtualIOMapping_data_t test;


//MainApp::MainApp()
//{
	// TODO Auto-generated constructor stub
//}

// Initialize singleton instance

MainApp::MainApp()
{
//    static MainApp instance;
//    return instance;
}

void MainApp::errorloop()
{
	//todo
	bool endless = true;
	while(endless)
	{//Eval Board zum test
		__NOP();
	}
	NVIC_SystemReset();
}

void MainApp::loop()
{
	if(!CANopenNode::instance().initNode())
	{
		errorloop();
	}
	//Definition der vorhandenen Pins
	//-------------------------------------------------------------------
	// Outputs
	//-------------------------------------------------------------------
	GPIOOutput LedGreenCAN(LD2_Pin, LD2_GPIO_Port, false);
	//GPIOOutput LedRedCAN(LD2_Pin, LD2_GPIO_Port, false);
	//GPIOOutput Output1(OUT1_Pin, , false);
	//GPIOOutput Output2(OUT2_Pin, OUT2_GPIO_Port, false);
	//-------------------------------------------------------------------
	// Zuordnung Pin <-> Funktion
	// virtualIOMapping_data_t auf Object 0x6200:xx schreiben, Slave empfängt vom Master
	//-------------------------------------------------------------------
	_OutputMap.setPinToMap(LedGreenCAN);
	//_OutputMap.setPinToMap(Output2);
//	for(uint8_t pinCnt = 0; pinCnt < _OutputMap.getPinCount(); pinCnt++)
//	{//connect virtual IOs from Object 0x6200 with pins
//		_OutputMap.setFunctionToPin(pinCnt, CANopenNode::instance().getODOutputFunctionMapping(pinCnt));
//	}
	//-------------------------------------------------------------------
	// Inputs
	//-------------------------------------------------------------------

	GPIOInput ButtonBlue(B1_Pin, B1_GPIO_Port,true, 10);
	//GPIOInput Input1(IN1_Pin, IN1_GPIO_Port, false, 5);
	//GPIOInput Input2(IN2_Pin, IN2_GPIO_Port, false, 5);
	//GPIOInput Input3(IN3_Pin, IN3_GPIO_Port, false, 5);
	//GPIOInput Input4(IN4_Pin, IN4_GPIO_Port, false, 5);
	//-------------------------------------------------------------------
	// Zuordnung Pin <-> Funktion
	// virtualIOMapping_data_t auf Object 0x6100:xx schreiben, Slave sendet an Master
	//-------------------------------------------------------------------
	_InputMap.setPinToMap(ButtonBlue);
	//_InputMap.setPinToMap(Input1);
	//_InputMap.setPinToMap(Input2);
	//_InputMap.setPinToMap(Input3);
	//_InputMap.setPinToMap(Input4);
	//for( uint8_t pinCnt = 0; pinCnt < _InputMap.getPinCount(); pinCnt++)
	//{//connect virtual IOs from Object 0x6100 with pins
	//	_InputMap.setFunctionToPin(pinCnt, CANopenNode::instance().getODInputFunctionMapping(pinCnt));
	//}


//	static bool lastButtonState = false;
//    static auto lastDebounceTime = std::chrono::steady_clock::now();
//    const int debounceDelay = 20; // 50 milliseconds debounce delay
	IOHandler::instance().initializeIO();
	while(true)
	{
		CANopenNode::instance().process();
		LedGreenCAN.setOutput(CANopenNode::instance().isLEDGreenOn());
		//LedRedCAN.setOutput(CANopenNode::instance().isLEDRedOn());
		
		//IOHandler::instance().initLEDs();
		//IOHandler::instance().libCOL_process(_hardware->GetTick());
		//canopen_app_interrupt();

		// loop über alle IO Pins
		execInputPins();
		execOutputPins();
		


//		bool currentButtonState = ButtonBlue.isPinOn();
//        auto now = std::chrono::steady_clock::now();
//        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastDebounceTime).count();
//
//        if (currentButtonState != lastButtonState) {
//            lastDebounceTime = now;
//        }
//
//        if ((elapsedTime > debounceDelay) && (currentButtonState != lastButtonState))
//		{
//            if (currentButtonState) {
//                loopCounter++;
//            }
//            lastButtonState = currentButtonState;
//        }

		//virtualIOMapping_data fifoData;
//		while(CANopenNode::instance().fifo_sendFunctionMapping.read(fifoData))
//        {
//            test = fifoData;
//			//CANopenNode::instance().triggerPDOsend();
//			if (OD_set_value(OD_ENTRY_H6011_virtualOutputMapping, 0, &fifoData, sizeof(virtualIOMapping_data_t), true) == ODR_OK)
//             {
//                 // Trigger the PDO send
//                 CANopenNode::instance().triggerPDOsend();
//             }
//
//        }
    }
}

void MainApp::execInputPins()
{
	CiA417_virtualIOMapping tmp_IOMapping;
	for(uint8_t pinCnt = 0; pinCnt < _InputMap.getPinCount(); pinCnt++)
	{
		tmp_IOMapping.get_mutable_virtualIOMapping() = _InputMap.getPinMapping(pinCnt);
		if(_InputMap.getGpio(pinCnt)->isDebouncePinOn() && tmp_IOMapping.get_virtualIOMapping().functionData == 0)
		{
			tmp_IOMapping.get_mutable_virtualIOMapping().functionData = 1;
			_InputMap.setFunctionToPin(pinCnt, tmp_IOMapping.get_virtualIOMapping());
			CANopenNode::instance().fifo_sendFunctionMapping.write(tmp_IOMapping.get_mutable_virtualIOMapping());
			//CANopenNode::instance().triggerPDOsend();
			CANopenNode::instance().sendInputs();

		}
		else if(!_InputMap.getGpio(pinCnt)->isDebouncePinOn() && tmp_IOMapping.get_virtualIOMapping().functionData == 1)
		{
			tmp_IOMapping.get_mutable_virtualIOMapping().functionData = 0;
			_InputMap.setFunctionToPin(pinCnt, tmp_IOMapping.get_virtualIOMapping());
			CANopenNode::instance().fifo_sendFunctionMapping.write(tmp_IOMapping.get_mutable_virtualIOMapping());
			CANopenNode::instance().triggerPDOsend();
		}
	}
}

void MainApp::execOutputPins()
{
	CiA417_virtualIOMapping tmp_data;
	CiA417_virtualIOMapping tmp_IOMapping;
	while(CANopenNode::instance().fifo_recvFunctionMapping.read(tmp_data.get_mutable_virtualIOMapping()))
	{
		_CmdHandler.execOutputCmd(tmp_IOMapping.get_mutable_virtualIOMapping());
		for(uint8_t subindex = 0; subindex < _OutputMap.getPinCount(); subindex++)
		{
			tmp_data.get_mutable_virtualIOMapping() = CANopenNode::instance().getODOutputFunctionMapping(subindex);
			if(tmp_IOMapping.isEqualExcludingData(tmp_data.get_virtualIOMapping()))
			{
				if(tmp_IOMapping != tmp_data)
				{
					//todo: check if toggle is enough, because inverted, frequency ...
					_OutputMap.getGpio(subindex)->toggle();
				}
				_OutputMap.setFunctionToPin(subindex, tmp_IOMapping.get_virtualIOMapping());
			}
		}
	}
}

/*---------------------------------------------------------------------------------------
 * All C calls from main.c
 * use as interface functions from C to C++
 *-------------------------------------------------------------------------------------*/
extern "C"
{
	//Callback for Timer interrupt every 1ms
	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
	{
		if(htim->Instance == CANopenNode::instance().getTimerHandler()->Instance)
		{
			CANopenNode::instance().timeHandler();
		}
	}

	void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
	{
		if(hcan->Instance == CANopenNode::instance().getCANHandler()->Instance)
		{
			//test
			CANopenNode::instance().timeHandler();
		}
	}

	void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan)
	{
		if(hcan->Instance == CANopenNode::instance().getCANHandler()->Instance)
		{
			//test
			CANopenNode::instance().timeHandler();
		}
	}

	//Callback for CAN Error
	void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
	{
		if(hcan->Instance == CANopenNode::instance().getCANHandler()->Instance)
		{
			CANopenNode::instance().errorHandler();
		}
	}

	/*
	 * Callback for Input Pins
	 *
	 * Different  Ports?
	 * Only one port interrupt may be active at one time for a given pin number.
	 * See the SYSCFG_EXTICRx register for the underlying hardware limitation.
	 */
/*
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
	{

		if(GPIO_Pin == B1_Pin)
		{//Eval Board zum test
			__NOP();
		}
	}
*/

}// end "C"
