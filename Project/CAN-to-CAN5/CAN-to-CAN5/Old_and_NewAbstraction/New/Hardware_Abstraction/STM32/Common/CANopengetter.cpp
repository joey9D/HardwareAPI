#include "CANopengetter.h"



// int CANopengetter::CANopenNode_Init() 

// {
//     // Initialize the CANopenNode with the desired settings

//     canopen.canopen_app_init(); // Pass the appropriate parameter if needed
// }


// uint8_t CANopengetter::CANopenNode_Process() 
// {
//     // Process the CANopenNode tasks
//     canopen.canopen_app_process();
// }

// uint32_t CANopengetter::CANopenNode_Reset() 
// {
//     // Reset the CANopenNode state
//     canopen.canopen_app_resetCommunication();
// }
// void CANopengetter::CANopenNode_Interrupt() 
// {
//     // Handle the CANopenNode interrupt
//     canopen.canopen_app_interrupt();
// }


// bool CANopengetter::isnodeIdValid() 
// {
//     if (canopenNodeSTM32_t->desiredNodeID!= canopenNodeSTM32_t->activeNodeID)
//     {
//         return false; // Node ID is not valid
//     }

//     else 
//     {
//         return true; // Node ID is valid
//     }

// }


// bool CANopengetter::getNodestate(int state)
// {
//     if (state ==0)
//     {
//          nodestate= false; // Node is not in the desired state
//     }

//     else
//     {
//         nodestate = true ; // Node is in the desired state
//     }


// }

// void CANopengetter::timingHandler()
// {
//     if (nodestate)
//     {
//         canopen.canopen_app_interrupt();
//     }

// }

	//Callback for Timer interrupt every 1ms

