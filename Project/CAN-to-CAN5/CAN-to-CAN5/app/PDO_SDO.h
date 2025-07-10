#ifndef PDO_SDO_H
#define PDO_SDO_H


#include "../basic/stack_fifo.h"
#include "COL_EventTypes.h"
#include "COL_EventSubject.h"
#include <queue>
#include "Hardware_Factory.h"
#include "CiA417_CmdHandler.h"
#include "CiA417_Gateway.h"
#include "CiA417_virtualIOMapping.h"


// class CANopenNode;
class PDO_SDO
{
    


 public: 
  PDO_SDO(HardwareInterface* hardware ); // Constructor to initialize the PDO_SDO instance with a CANopenNode pointer and optional HardwareInterface pointer.

  void RegisterPDO_SDOCallbacks(); // Registers Callbacks for TPDO , RPDO and SDO.
  static void RPDO_PreCallback(void* object); // Callback function for RPDOs assigns value to RPDO object after Callback gets triggered.
  void QueueTPDO(virtualIOMapping_data_t& data); // Queues TPDO ; RPDO and SDO Signals.
  void QueueRPDO(const virtualIOMapping_data_t& data); // Queues RPDO Signals.
  void checkQueue(); // Checks the queue for any pending signals and processes them accordingly.
private:
    static void static_callbackSdoVirtOMapData(void* object); // Static callback function for SDOs.
    void callbackSdoVirtOMapData(void* object); // Callback function for SDOs, processes the received data.
    void adoptVirtOMapData(virtualIOMapping_data_t& data); // Adopts the virtual I/O mapping data for further processing.
    inline static COL_EventBus g_eventBus; // observer bus for notification
    inline static MyRPDOObserver rpdoObs; // rpdo observer bus
    inline static ODLogger odLogger; // OD change logger for the observer 
    HardwareInterface* hardware = nullptr; // Pointer to the HardwareInterface instance
    std::queue<virtualIOMapping_data_t> tpdoqueue; // Stack for TPDO FIFO
    std::queue<virtualIOMapping_data_t> rpdoqueue; // Stack for RPDO FIFO
    //HelperFunctions help;
    CiA417_CmdHandler _CmdHandlers;
    CiA417_Gateway _CiA417Gateway;
    CiA417_virtualIOMapping _virtOMapData;
	CiA417_virtualIOMapping _oldVirtOMapData;

    struct RPDOCallbackContext
    {
        uint8_t index;
        PDO_SDO* pdo_sdo =nullptr;
        
        

    };
};

#endif // PDO_SDO_H
