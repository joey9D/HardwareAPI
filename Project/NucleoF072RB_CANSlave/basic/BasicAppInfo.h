/*
 * BasicAppInfo.h
 *
 *  Created on: Jul 29, 2024
 *      Author: michael.grathwohl
 */

#ifndef BASICAPPINFO_H_
#define BASICAPPINFO_H_

#include <cstdint>

typedef struct
{
	uint32_t checksum;
	uint32_t invers_checksum;
	uint32_t size;
	uint32_t info;
}_APP_VERIFICATION_t;

typedef struct
{
	uint16_t major;
	uint16_t minor;
	uint16_t revision;
	uint16_t variant;
}_APP_VERSION_t;

typedef struct
{
	_APP_VERIFICATION_t verify;
	_APP_VERSION_t version;
}_APP_INFO_t;

#endif /* BASICAPPINFO_H_ */
