/*
 * CiA417Verifier.h
 *
 *  Created on: Jan 29, 2024
 *      Author: michael.grathwohl
 */

#ifndef CIA417_GATEWAY_H_
#define CIA417_GATEWAY_H_

#include "CiA417_LiftTypes.h"

class CiA417_Gateway
{
public:
	CiA417_Gateway();
	virtual ~CiA417_Gateway();

	bool isOutputBfValid(const uint8_t &Bf);
	bool isOutputSfValid(const uint8_t &Bf, const uint8_t &Sf);
	bool isInputBfValid(const uint8_t &Bf);
	bool isInputSfValid(const uint8_t &Bf, const uint8_t &Sf);
	bool isLiftValid(const uint8_t &Lift);
	bool isFloorValid(const uint8_t &Floor);
	bool isDoorValid(const uint8_t &Door);

private:

};

#endif /* CIA417_GATEWAY_H_ */
