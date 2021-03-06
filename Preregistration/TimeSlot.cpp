#include "TimeSlot.h"
#include "ClientServerInterface.hpp"

TimeSlot::TimeSlot()
{
	mDay = DAYS_END;
	mStartHour = 0;
	mStartMinutes = 0;
	mEndHour = 0;
	mEndMinutes = 0;
}

TimeSlot::TimeSlot(Day day, unsigned int startHour, unsigned int startMinutes, unsigned int endHour, unsigned int endMinutes) :
	mDay (day), mStartHour (startHour), mStartMinutes (startMinutes), mEndHour (endHour), mEndMinutes (endMinutes)
{
}

TimeSlot::Day TimeSlot::getDay()
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

std::string TimeSlot::getTimeString()
{
	return std::to_string(mStartHour) + ":" + std::to_string(mStartMinutes) + " - " + std::to_string(mEndHour) + ":" + std::to_string(mEndMinutes);
}

std::string  TimeSlot::getDayString()
{
	switch (mDay)
	{
	case MONDAY: return "M"; break;
	case TUESDAY: return "T"; break;
	case WEDNESDAY: return "W"; break;
	case THURSDAY: return "R"; break;
	case FRIDAY: return "F"; break;
	case SATURDAY: return "Sa"; break;
	case SUNDAY: return "Su"; break;
	default: return " ";
	}
}

TimeSlot::Day TimeSlot::stringToDay(const std::string & dayString)
{
	if (dayString == "M")
	{
		return MONDAY;
	}
	else if (dayString == "T")
	{
		return TUESDAY;
	}
	else if (dayString == "W")
	{
		return WEDNESDAY;
	}
	else if (dayString == "R")
	{
		return THURSDAY;
	}
	else if (dayString == "F")
	{
		return FRIDAY;
	}
	else if (dayString == "Sa")
	{
		return SATURDAY;
	}
	else if (dayString == "Su")
	{
		return SUNDAY;
	}
	else
	{
		return DAYS_END;
	}
}

bool TimeSlot::conflictsWith(TimeSlot * ts)
{
	return (mDay != ts->mDay) && 
		(((ts->mStartHour <= mStartHour && ts->mStartMinutes < mStartMinutes) && (mStartHour <= ts->mEndHour && mStartMinutes < ts->mEndMinutes)) || 
			((ts->mStartHour <= mEndHour &&	ts->mStartMinutes < mEndMinutes) && (mEndHour <= ts->mEndHour && mEndMinutes < ts->mEndMinutes)) ||
			((mStartHour <= ts->mStartHour && mStartMinutes < ts->mStartMinutes) && (ts->mEndHour <= mEndHour && ts->mEndMinutes < mEndMinutes)));
}

std::string TimeSlot::serialize()
{
	return getDayString() + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string(mStartHour) +
		ClientServerInterface::TIMESLOT_DELIMITER + std::to_string(mStartMinutes) + ClientServerInterface::TIMESLOT_DELIMITER + 
		std::to_string(mEndHour) + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string(mEndMinutes);
}
