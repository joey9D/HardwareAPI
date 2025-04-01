/*
 * input_base.h
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */

 #ifndef INPUT_BASE_H_
 #define INPUT_BASE_H_

#include "timer.h"

class Input_base
{
    private:
        uint32_t _debounceTime = 0;
        uint8_t _debouceState = 0;
        Timer _debounceTimer;
    
    public:
        Input_base(uint32_t debounceTime, uint8_t debounceState, Timer debounceTimer);
        ~~Input_base() = default;
        bool isInputPinOn() const;
        bool isDebouncePinOn() const;
        
}


 #endif /* INPUT_BASE_H_ */
