#pragma once

class TimeSlot
{

public:
	enum Day {
		MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, DAYS_END
	};

	TimeSlot();
	TimeSlot(Day day, unsigned int startHour, unsigned int startMinutes, unsigned int endHour, unsigned int endMinutes);

	Day getDay();
	unsigned int getStartHour();
	unsigned int getStartMinutes();
	unsigned int getEndHour();
	unsigned int getEndMinutes();

private:
	Day mDay;
	unsigned int mStartHour;
	unsigned int mStartMinutes;
	unsigned int mEndHour;
	unsigned int mEndMinutes;
};


