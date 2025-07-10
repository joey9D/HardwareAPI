#include "CANopenMaster.h"


CANopenMaster::CANopenMaster(HardwareInterface* hardware)
    : _hardware(hardware)
{
    // Constructor to initialize the CANopenMaster instance
    // The hardware interface is passed as a parameter
   
}


bool CANopenMaster::initMaster()
{
	
	// Initialize the CANopenNodeSTM32 structure with default values
    assert(_hardware != nullptr); // Ensure hardware interface is not null
	_hardware->setHandles(1); // Set the hardware handles for CANopenMaster , Node ID is set to 0 by default, can be changed later	
	int16_t error = _hardware->CANopen_Init(); // Initialize the CANopen
	if(error != CO_ERROR_NO || _hardware->isIdValid() == false)
	{//init failed
		setLastError(1);
		setinitState(0);
	}
	else
	{// init succesful
		setinitState(1);
		setCallbackFunctions();
	}
	return isMasterInitOk();
}


void CANopenMaster::InitMasterStack()

{	
	
	
	if(!initMaster())
	{
		errorloop();
	}

}

void CANopenMaster::errorloop()
{
	bool endless = true;
	while(endless)
	{//Eval Board zum test
		__NOP();
	}
	_hardware->System_Reset(); // Reset the system if initialization fails
}

bool CANopenMaster::isMasterInitOk()
{
	if(_initState == 0)
	{
		_hardware->getstate(_initState);
		return false;
	}
	else
	{
		_hardware->getstate(_initState);
		return true;
	}
}



HardwareInterface* CANopenMaster::getHardwareInterface() 
{
    return _hardware;
}


CiA417_CmdHandler& CANopenMaster::getCiA417_CmdHandler()
{
	return _CmdHandlers;
}


void CANopenMaster::initialize() 
{

	// static GPIOHandler gpioHandlerInstance; // Use a static instance to avoid dynamic allocation
    // _gpioHandler = &gpioHandlerInstance;

    // static PDO_SDO pdoSdoInstance;
    // _pdoSdo = &pdoSdoInstance;

    // static NMT_LED nmtLedInstance;
    // _nmtLed = &nmtLedInstance;
  
}

void CANopenMaster::setinitState(uint8_t val)
{
	_initState = val;
}

uint32_t CANopenMaster::getLastError()
{
	return _error;
}

void CANopenMaster::setLastError(uint32_t val)
{
	_error = val;
}

void CANopenMaster::setCallbackFunctions()
{
	_hardware->RegisterMasterCallbacks(); // Register the callback functions for the master node events
	
}

void CANopenMaster::process()
{
	_hardware->CANopen_Process();
    MasterOperation(); // Call the MasterOperation function to handle the state machine

	//  TODO Add error Handling
}

void CANopenMaster::timeHandler()
{
	if(isMasterInitOk())
	{
		_hardware->CANopen_Interrupt();
	}
}

void CANopenMaster::errorHandler()
{
	if(isMasterInitOk())
	{
		_hardware->errorHandler();
	}
}

void CANopenMaster::MasterOperation()
{
    switch (Master_state)
    {
        case CANopenMasterStates::CANopenMaster_Init:
            setState(CANopenMasterStates::CANopenMaster_ResetNodes);
            break;
        case CANopenMasterStates::CANopenMaster_ResetNodes:
			if(_hardware->getNMTinternalstate(CO_NMT_PRE_OPERATIONAL))
			{
            	setState(CANopenMasterStates::CANopenMaster_PreOp);
			}
            break;
        case CANopenMasterStates::CANopenMaster_PreOp:
			// Send everyone including CANMaster in Operational Mode & Check if CAN Master is allowed to go into operational Mode TODO.
			if (_hardware->allNodesBooted()) // Check if all nodes are booted
			{
				setState(CANopenMasterStates::CANopenMaster_StartNodes);
			}
            // Handle pre-operational state
            break;
        case CANopenMasterStates::CANopenMaster_StartNodes:
            // Handle start nodes state
			_hardware->setNMTinternalstate(CO_NMT_OPERATIONAL);
			_hardware->Delay(500);
			_hardware->MasterNodesendCommand(CO_NMT_ENTER_OPERATIONAL); // Send command to enter operational state // Default sends to all nodes (nodeId = 0)
			
			if(_hardware->getNMTinternalstate(CO_NMT_OPERATIONAL))
			{
				setState(CANopenMasterStates::CANopenMaster_Op);
			}

            break;
        case CANopenMasterStates::CANopenMaster_CheckOp:
            // Handle check operational state
			// Add loop checking if all nodes are in operational state using the 1016 array which must  be set by then also gets updated.
            break;
        case CANopenMasterStates::CANopenMaster_Op:
			_hardware->NodeStateHandler(); // Call the NodeStateHandler to manage node states
			
            // Handle operational state
            break;
        case CANopenMasterStates::CANopenMaster_Stop:
            // Handle stop state
            break;
        case CANopenMasterStates::CANopenMaster_Error:
            // Handle error state
            break;
        case CANopenMasterStates::CANopenMaster_Unknown:
            // Handle unknown state
            break;
    }
} // Todo add another state for SDO Handling and PDO handling

