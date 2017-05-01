#include "TimeSlot.h"

TimeSlot::TimeSlot()
{
	mDay = DAYS_END;
	mStartHour = 0;
	mStartMinutes = 0;
	mEndHour = 0;
	mEndMinutes = 0;
}

TimeSlot::TimeSlot::TimeSlot(Day day, unsigned int startHour, unsigned int startMinutes, unsigned int endHour, unsigned int endMinutes)
{
	mDay = day;
	mStartHour = startHour;
	mStartMinutes = startMinutes;
	mEndHour = endHour;
	mEndMinutes = endMinutes;
}

Day TimeSlot::getDay()
{
	return mDay;
}

unsigned int TimeSlot::getStartHour()
{
	return mStartHour;
}

unsigned int TimeSlot::getStartMinutes()
{
	return mStartMinutes;
}

unsigned int TimeSlot::getEndHour()
{
	return mEndHour;
}

unsigned int TimeSlot::getEndMinutes()
{
	return mEndMinutes;
}
