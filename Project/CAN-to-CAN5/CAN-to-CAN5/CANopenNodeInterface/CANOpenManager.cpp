#include "CANOpenManager.h"

CANOpenManager::CANOpenManager()
    : hardware(HardwareFactory::Create()),
      Master(hardware),
      node(hardware),
      pdo_sdo( hardware),
      nmt_led( hardware),
      gpioHandler(&pdo_sdo, hardware),
      nketHandler(hardware)
{
    // ...
    // ...existing code...
}


void CANOpenManager::InitIO()
{  
    // Unused Dependency injection used instead.
    // node.initialize(); // Initialize dependent objects 
    
    // Initialize GPIOs and other hardware peripherals
    gpioHandler.MapIOPins();
    pdo_sdo.RegisterPDO_SDOCallbacks(); // Register Callbacks for TPDO , RPDO and SDO.
    nmt_led.registerNMTStateChangeCallback(); // Register NMT state change callback
}


void CANOpenManager::InitCANopenStack()
{

    if (currentMode == NODE) {
        node.InitNodeStack();
    } else if (currentMode == MASTER) {
        Master.InitMasterStack();
    }
    nketHandler.initNKETStack();

    // Add interuupt for can error and also timer handler functions.
}


void CANOpenManager::CheckSignals()
{   
    #ifdef REGISTERIO
	gpioHandler.InterruptGPIOInputHandler();
	#endif//
	gpioHandler.InterruptGPIOInputHandler();
	pdo_sdo.checkQueue(); // Check the queue for any pending signals and process them accordingly
	gpioHandler.OutputPins(); // Update the output pins based on the current state
}


void CANOpenManager::Startloop()
{
    if (currentMode == NODE) {
        node.process();
    } else if (currentMode == MASTER) {
        Master.process();
    }
    CheckSignals(); // Check and process input signals, update outputs, and handle RPDO queues
    nmt_led.LEDIndication(); // Update the LED indication based on the current NMT state
}

void CANOpenManager::setMode(Mode mode)
{
    currentMode = mode;
}
