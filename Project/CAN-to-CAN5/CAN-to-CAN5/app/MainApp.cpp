/*
 * MainApp.cpp
 *
 *  Created on: Dec 6, 2023
 *      Author: michael.grathwohl
 */
#include "MainApp.h"
#include "globals.h"
#include "CANopenNode.h"
#include "../basic/Timer.h"
#include <chrono>
#include "OD.h"
#include "IOHandler.h"

MainApp::MainApp()
{
	// Constructor intentionally left blank
}

void MainApp::loop()
{
	_canOpenManager.setMode(CANOpenManager::Mode::MASTER); // Set the mode to MASTER OR NODE for CANopenMaster OR CANopenNode operation
	_canOpenManager.InitCANopenStack(); // Initialize CANopen stack

	_canOpenManager.InitIO(); // Initialize GPIOs and other hardware peripherals // register Callbacks for TPDO , RPDO and SDO.

	while(true)
	{
		_canOpenManager.Startloop();
    }
}




