#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <QString>

enum Day {
    SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, DAYS_END
};

class TimeSlot
{
private:
    Day mDay;
    unsigned int mStartHour;
    unsigned int mStartMinutes;
    unsigned int mEndHour;
    unsigned int mEndMinutes;

public:
    TimeSlot();
    TimeSlot(Day day, unsigned int startHour, unsigned int startMinutes, unsigned int endHour, unsigned int endMinutes);

    Day getDay();
    unsigned int getStartHour();
    unsigned int getStartMinutes();
    unsigned int getEndHour();
    unsigned int getEndMinutes();

    QString getTimeString();
    QString getDayString();
};

#endif // TIMESLOT_H
