/*
 * globals.h
 *
 *  Created on: Dec 7, 2023
 *      Author: michael.grathwohl
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_


//Can
#define DEFAULT_CAN_NODE_ID			17
#define DEFAULT_CAN_TIMERIRQ_IN_US	1000
//#define DISABLE_CAN

//LEDS
#define BRIGHTNESS				100
#define LED_STRIP_LENGTH_CM		(8*100)
#define LED_STRIP_COUNT			(60*8) //60leds/meter * 5 meter = 300
#define LED_STRIP_REVERSE		0	//0 = normal, 1 = reverse
#define LED_OFF_TIMEOUT_MSEC	60000 //1min * 60 * 1000

//Moving Average Filter
#define AVERAGE_FILTER			10
#define AVERAGE_FILTER_MAX_DIST	5 // in cm

#define CABIN_LENGTH_CM				200 //length of cabin
//#define ELEVATOR_SHAFT_LENGTH_CM	900

#endif /* GLOBALS_H_ */
