#include "NMT_LED.h"

NMT_LED::NMT_LED(HardwareInterface* hardware)
    : hardware(hardware) {}

void NMT_LED::LEDIndication()
{   
    /*
	 * CANopen green led - run led:
	 * - flickering: 	LSS configuration state is active
	 * - blinking: 		device is in NMT pre-operational state
	 * - single flash: 	device is in NMT stopped state
	 * - triple flash: 	a software download is running in the device
	 * - on: 			device is in NMT operational state
	*/
    bool state ;


    if(hardware->getLedgreenstate() != 0)
    {
        state = true;
    }
    else
    {
        state = false;
    } 

    if (_oldState != state) 
        {
            _oldState = state;
            hardware->LEDblink(state); // LED Pin and Port for each port must be defined seperately  // Set LED pin and Port from config file in HardwareInterface

        }
}



void NMT_LED::registerNMTStateChangeCallback()
{  
    
        // Register the callback for NMT state changes
        CO_NMT_t* nmt = reinterpret_cast<CO_NMT_t*>(hardware->getNMT());
        CO_NMT_initCallbackChanged(nmt, onNMTStateChange);
    
   
}

void NMT_LED::setNMTState(CO_NMT_internalState_t state)
{
    _currentNMTState = state; // to be used somewhere
    // Optional: trigger system behavior
    // if (state == CO_NMT_STOPPED) handleSafetyFallback();
}

void NMT_LED::onNMTStateChange(CO_NMT_internalState_t newState) // Very inefficient needs to be changed as static function would with every call and create new object for the class 
{
    g_nmtState = newState;  // Update global tracker

    // this->setNMTState(newState); // Update the NMT state in the NMT_LED class
}
