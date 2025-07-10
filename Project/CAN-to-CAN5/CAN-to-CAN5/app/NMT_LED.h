#ifndef NMT_LED_H
#define NMT_LED_H

#include "COL_EventTypes.h"
#include "COL_EventSubject.h"
#include "Hardware_Factory.h"



// class CANopenNode;

class NMT_LED
{
    public:
    NMT_LED(HardwareInterface* hardware); // Constructor to initialize the NMT_LED instance with a HardwareInterface pointer and optional CANopenNode and CANopenMaster pointers

    void registerNMTStateChangeCallback(); // Registers the NMT state change callback
    void setNMTState(CO_NMT_internalState_t state); // Sets global NMT state change variable
    void LEDIndication(); // LED indication function to be called in the main loop
    static void onNMTStateChange(CO_NMT_internalState_t newState); // Static function to handle NMT state changes


    private:

    inline static CO_NMT_internalState_t g_nmtState = CO_NMT_INITIALIZING; // Send to NMT_LED
    inline static COL_EventBus g_eventBus; // Global event bus instance
    bool _oldState = true; // Previous state of the LED
    CO_NMT_internalState_t _currentNMTState = CO_NMT_INITIALIZING;
    HardwareInterface* hardware = nullptr; // Pointer to the HardwareInterface instance
};
    
#endif // NMT_LED_H
