#include "PDO_SDO.h"
#include "CANopenNode.h"


PDO_SDO::PDO_SDO(HardwareInterface* hardware) : hardware(hardware) {}

void PDO_SDO::RegisterPDO_SDOCallbacks()
{
   //Register RPDO Callbacks based on the number of RPDOs assigned in the stack
   static RPDOCallbackContext rpdoCtxArray[OD_CNT_RPDO];
   CO_RPDO_t* rpdo = reinterpret_cast<CO_RPDO_t*>(hardware->getRPDO());
   //CO_RPDO_t* rpdo = CANopenNode::instance().CO->RPDO; // Get the RPDO object from the CANopen instance
   for (uint8_t i = 0; i <  OD_CNT_RPDO; ++i) 
    {
        rpdoCtxArray[i].index = i;
        rpdoCtxArray[i].pdo_sdo = this;  // <-- This is critical!
        
        CO_RPDO_initCallbackPre(rpdo , &rpdoCtxArray[i], RPDO_PreCallback); // Send to PDO_SDO
    } 


    // Register SDO Callback
    CO_SDOserver_t* sdo =reinterpret_cast<CO_SDOserver_t*>(hardware->getSDO());

    CO_SDOserver_initCallbackPre(sdo, this,
        static_callbackSdoVirtOMapData); // Connect this to RPDO as then it can be used to transmit the Signal
}

void PDO_SDO::RPDO_PreCallback(void* object)  // Send to PDO_SDO 
{
    auto* ctx = static_cast<RPDOCallbackContext*>(object);
    if (!ctx) 
    {
        return;
    }
    if (ctx->pdo_sdo == nullptr)
    {
    	return;
    }

    const CO_RPDO_t* rpdo = reinterpret_cast<CO_RPDO_t*>(ctx->pdo_sdo->hardware->getRPDOwithIndex(ctx->index)) ;
    const virtualIOMapping_data_t* data = reinterpret_cast<const virtualIOMapping_data_t*>(rpdo->CANrxData); // change to static cast after test .. todo
    ctx->pdo_sdo->QueueRPDO(*data); // Enqueue the RPDO data for processing

}

void PDO_SDO::QueueRPDO(const virtualIOMapping_data_t& mapping) 
{
    auto copy = mapping;
    // CANopenNode::instance().getPDO_SDO().rpdoqueue.write(copy);  // queue it
    rpdoqueue.push(copy);  // queue it

} 

void PDO_SDO::QueueTPDO(virtualIOMapping_data_t& mapping)
{
    tpdoqueue.push(mapping);  // queue it
}


void PDO_SDO::checkQueue() // Here only RPDO Queue is checked because TPDOs are sent in ( Input Pin Trigger , Output Status Trigger and so on)
{
    virtualIOMapping_data_t data;

    // Process all RPDOs in the queue
    while (!rpdoqueue.empty())
    {
        data = rpdoqueue.front();
        rpdoqueue.pop();
        // Execute the output command based on the received mapping
        _CmdHandlers.execOutputCmd(data);

        g_eventBus.rpdo.notifyrpdo(data); // First add Handler and then notify the event bus about the RPDO command

    }

    virtualIOMapping_data_t data1;

    while (!tpdoqueue.empty())
    {
        data1 = tpdoqueue.front();
        tpdoqueue.pop();
        // Send the TPDO data to the Object Dictionary
        if (OD_set_value(OD_ENTRY_H6010_virtualInputMapping, 0, &data1, sizeof(virtualIOMapping_data_t), true) == ODR_OK) 
        {
            // Trigger the PDO send request
            hardware->getTPDOsend(); // This will set the sendRequest flag for the TPDO
        }

        g_eventBus.tpdo.notifyTPDO(data1);  // Notify the event bus about the TPDO command

        // Notify the event bus about the TPDO command
    }
    
    




}

void PDO_SDO::static_callbackSdoVirtOMapData(void *object)
{
	if(object != nullptr) {
		static_cast<PDO_SDO*>(object)->callbackSdoVirtOMapData(object);
	}
}

void PDO_SDO::callbackSdoVirtOMapData(void *object)
{
	assert(object != nullptr);
	CO_SDOserver_t* sdo =reinterpret_cast<CO_SDOserver_t*>(hardware->getSDO());
	assert(sdo != nullptr);

	adoptVirtOMapData(*reinterpret_cast<virtualIOMapping_data_t *>(sdo->CANrxData));
}

void PDO_SDO::adoptVirtOMapData(virtualIOMapping_data_t &data)
{
	_virtOMapData.set_virtualIOMapping(data);

	if(_virtOMapData != _oldVirtOMapData
		&& _CiA417Gateway.isLiftValid(_virtOMapData.get_virtualIOMapping().lift)
		&& _CiA417Gateway.isDoorValid(_virtOMapData.get_virtualIOMapping().door)
		&& _CiA417Gateway.isFloorValid(_virtOMapData.get_virtualIOMapping().floor)
	)
	{
		QueueRPDO(data);
		_oldVirtOMapData = _virtOMapData;
	}
}
















