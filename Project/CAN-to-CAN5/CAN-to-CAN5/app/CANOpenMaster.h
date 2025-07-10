#ifndef CANOPENMASTER_H_
#define CANOPENMASTER_H_

#include <cstdint>
#include "../basic/singleton.h"
#include "CiA417_VirtualIOMapping.h"
#include "FunctionMapping.h"
#include "../basic/stack_fifo.h"
#include "CiA417_Gateway.h"
#include "Hardware_Factory.h"
#include "CiA417_CmdHandler.h"

/* CanOpenMaster.h
 * 
 *  Created on: June 18, 2025                                                                          
    Created by K.Singh

    CANOpenMaster class must handle all the fucntionality of the CANopen CiA417 Master, including , 
    NMT state management, PDO handling, SDO handling, and error handling , as well as the LSS configuration.

    This requires CiA 301 and CiA 417 specifications to be implemented in the CANOpenMaster class.


*/
class CANopenMaster
{


    public:
    CANopenMaster(HardwareInterface* hardware); // Constructor to initialize the CANopenMaster instance

    enum class CANopenMasterStates : uint8_t
    {
        CANopenMaster_Init = 0x00,
        CANopenMaster_ResetNodes,
        CANopenMaster_PreOp,
        CANopenMaster_StartNodes,
        CANopenMaster_CheckOp,
        CANopenMaster_Op,
        CANopenMaster_Stop,
        CANopenMaster_Error,
        CANopenMaster_Unknown
    };

    
    void initialize(); // Initialize dependent objects

    bool initMaster();
	bool isMasterInitOk();
	void errorloop();
	uint32_t getLastError();
	
	void InitMasterStack();

    void setCallbackFunctions();
    inline CANopenMasterStates& getState() 
    {
        return Master_state;
    }

    inline void setState(CANopenMasterStates current_state) 
    {
        Master_state = current_state;
    }

	void process();
    void MasterOperation();
	void timeHandler();
	void errorHandler();
    HardwareInterface* getHardwareInterface();
	CiA417_CmdHandler& getCiA417_CmdHandler();

	private:
    HardwareInterface* _hardware =nullptr ;           // Static pointer to HardwareInterface
	CiA417_CmdHandler _CmdHandlers;


    void setinitState(uint8_t val);
	void setLastError(uint32_t val);
    uint8_t _initState = 0;
    uint32_t _error = 0;
    CANopenMasterStates Master_state = CANopenMasterStates::CANopenMaster_Init;













   
    
};










































#endif /* CANOPENMASTER_H_ */
