#ifndef CANOPENMANAGER_H
#define CANOPENMANAGER_H


/*This file will serve as an interface between canopenstack and  application file 
this will be purely designed for an event driven mechanism which involves 
minimal looped functions . Goal is to achieve all functionality uing callback 
functions leaving only heartbeat generation in the loop which can also be handled by 
1 ms timer interrupt for a specific hardware. Challenge here is to make the events non 
blocking and not allow for any problems during simultaneous execuation of multiple 
processes. This will provide better low power mode configuration during microcontroller CPU idle time.*/

#include "CANopenNode.h"
#include "NMT_LED.h"
#include "PDO_SDO.h"
#include "GPIOHandler.h"
#include "CANOpenMaster.h"
#include "Hardware_Interface.h"
#include "NKET_Handler.h"


class CANOpenManager

{


public:
    enum Mode {NODE, MASTER}; // Enum to define the mode of operation, either NODE or MASTER
    CANOpenManager(); // Constructor to initialize the CANOpenManager instance
    void InitIO(); // Initialize GPIOs and other hardware peripherals as wells as Logging Observers , sets up callbacks for RPDO TPDO and SDO
    void InitCANopenStack(); // Initializes the CANopen stack provides timer details to the stack sets up error sitiation
    void Startloop();  // Starts the main loop for the application, which includes waiting for interrupts and processing CANopen events.
    void setMode(Mode mode); // Sets the mode of operation for the CANOpenManager, either NODE or MASTER
private:
    void CheckSignals(); // Checks and processes input signals, updates outputs, and handles RPDO queues
    HardwareInterface* hardware = nullptr; // Instance of the Hardware_Interface class to manage hardware interactions
    CANopenNode node; // Instance of the CANopenNode class to manage CANopen functionalities
    CANopenMaster Master;
    NKET_Handler nketHandler; // Instance of the NKET_Handler class to manage NKET functionalities
    PDO_SDO pdo_sdo; // Instance of the PDO_SDO class to manage PDO and SDO operations
    NMT_LED nmt_led; // Instance of the NMT_LED class to manage NMT state indication through LEDs
    GPIOHandler gpioHandler; // Instance of the GPIOHandler class to manage GPIO operations
    Mode currentMode = Mode::NODE; // Current mode of operation, default is NODE
    // Timer timer; // Instance of the Timer class to manage timing operations
};

	
#endif // CANOPENMANAGER_H
