/*
 * MainApp.h
 *
 *  Created on: Dec 6, 2023
 *      Author: michael.grathwohl
 */

#ifndef MAINAPP_H_
#define MAINAPP_H_

#ifdef __cplusplus

#include "../basic/singleton.h"
#include "FunctionMapping.h"
#include "CiA417_CmdHandler.h"


class MainApp
{
	SINGLETON(MainApp)
public:

	void loop();
	void errorloop();

	UART_HandleTypeDef *p_huart = nullptr;

private:
	MainApp();
	//virtual ~MainApp();

	HardwareInterface* _hardware;
	FunctionMapping<GPIOOutput, 8> _OutputMap;
	FunctionMapping<GPIOInput, 8> _InputMap;
	CiA417_CmdHandler _CmdHandler;

	void execInputPins();
	void execOutputPins();
};

#endif /* __cplusplus */

#endif /* MAINAPP_H_ */
