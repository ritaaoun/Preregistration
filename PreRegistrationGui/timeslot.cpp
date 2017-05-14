#include "timeslot.h"

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

QString TimeSlot::getTimeString()
{
    return QString::number(mStartHour) + ":" + QString::number(mStartMinutes) + " - " + QString::number(mEndHour) + ":" + QString::number(mEndMinutes);
}

QString TimeSlot::getDayString()
{
    switch(mDay)
    {
        case SUNDAY: return "Su"; break;
        case MONDAY: return "M"; break;
        case TUESDAY: return "T"; break;
        case WEDNESDAY: return "W"; break;
        case THURSDAY: return "R"; break;
        case FRIDAY: return "F"; break;
        case SATURDAY: return "Sa"; break;
        default: return " ";
    }
}

std::string TimeSlot::getDayStdString()
{
    QString day = getDayString();

    return day.toStdString();
}

void TimeSlot::setDay(int day)
{
    mDay = static_cast<Day>(day);
}

void TimeSlot::setStartHour(int startHour)
{
    mStartHour = startHour;
}

void TimeSlot::setStartMinutes(int startMinutes)
{
    mStartMinutes = startMinutes;
}

void TimeSlot::setEndHour(int endHour)
{
    mEndHour = endHour;
}

void TimeSlot::setEndtMinutes(int endMinutes)
{
    mEndMinutes = endMinutes;
}
