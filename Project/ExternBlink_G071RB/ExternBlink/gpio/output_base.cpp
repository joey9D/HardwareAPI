/*
 * output_base.cpp
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */


#include "output_base.h"

bool Output_base::isOutputPinOn() const {
    return _oldPinState;
}
