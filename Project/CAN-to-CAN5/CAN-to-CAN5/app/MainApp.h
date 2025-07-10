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
#include "CANopenManager.h"
#include "NKET_Handler.h"


class MainApp
{
public:
	MainApp();

	void loop();


private:
	
	CANOpenManager _canOpenManager;
	
};

#endif /* __cplusplus */

#endif /* MAINAPP_H_ */
