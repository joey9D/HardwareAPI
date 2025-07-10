/*
 * DateTime.h
 *
 *  Created on: Sep 6, 2023
 *      Author: michael.grathwohl
 */

#ifndef DATETIME_H_
#define DATETIME_H_

#include <cstdint>

class DateTime
{
public:
	DateTime() = delete;
	virtual ~DateTime() = delete;

	struct Date
	{
		uint16_t year;
		uint8_t month;
		uint8_t day;
	};

	struct Time
	{
		uint8_t hour;
		uint8_t min;
		uint8_t sec;
	};

	 static uint16_t countLeapYears(const Date &d)
	 {
	     uint16_t years = d.year;

	     // Check if the current year needs to be considered
	     // for the count of leap years or not
	     if(d.month <= 2)
	     {
	         years--;
	     }
	     // An year is a leap year if it is a multiple of 4,
	     // multiple of 400 and not a multiple of 100.
	     return ((years / 4) - (years / 100) + (years / 400));
	 }

	 static uint32_t getDifference(const Date &startDate, const Date &endDate)
	 {
	     // COUNT TOTAL NUMBER OF DAYS
	 	uint32_t startDays = 0;
	 	uint32_t endDays = 0;

	     // initialize count using years and day
	 	startDays = startDate.year * 365 + startDate.day;
	     // Add days for months in given date
	     for(uint8_t i = 0; i<(startDate.month - 1) && i<DaysOfMonth_size; i++)
	     {
	     	startDays += DaysOfMonth[i];
	     }
	     // Since every leap year is of 366 days,
	     // Add a day for every leap year
	     startDays += countLeapYears(startDate);

	     endDays = endDate.year * 365 + endDate.day;
	     for(uint8_t i = 0; i < (endDate.month - 1) && i<DaysOfMonth_size; i++)
	     {
	     	endDays += DaysOfMonth[i];
	     }
	     endDays += countLeapYears(endDate);

	     // return difference between two counts
	     return (endDays - startDays);
	 }

	 static uint32_t getTimeInMsec(const Time &t)
	 {
	 	return (getTimeInSec(t) * 1000);
	 }

	 static uint32_t getTimeInSec(const Time &t)
	 {
	 	return ((((t.hour * 60) + t.min) * 60) + t.sec);
	 }

private:
	static constexpr uint8_t DaysOfMonth[] =
	{
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};
	static const uint8_t DaysOfMonth_size = sizeof(DaysOfMonth)/sizeof(DaysOfMonth[0]);
};

#endif /* DATETIME_H_ */
