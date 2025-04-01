/*
 * output_base.h
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */

#ifndef OUTPUT_BASE_H_
#define OUTPUT_BASE_H_


//#include "gpio_base.h"

class Output_base
{
	protected:
		bool _oldPinState = true;
	public:
		bool isOutputPinOn() const;
		virtual void setPinOutput(bool activePinState);
		virtual void toggle();
};


#endif /* OUTPUT_BASE_H_ */
