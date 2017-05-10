#pragma once

#include "ISchedulable.h"
#include "TimeSlot.h"
#include "Section.hpp"

class Schedule {
public:
	Schedule(ISchedulable* schedulable);
	~Schedule();

	void generateSchedule();
	bool hasConflictWith(TimeSlot* timeSlot) const;
	bool hasConflictWith(std::vector<TimeSlot*> timeSlots) const;
	bool hasConflictWith(Section* section) const;
	bool containsConflict() const;

private:
	ISchedulable* mSchedulable;
	std::vector<TimeSlot*> mTimeSlots;
	bool mContainsConflict;
	Schedule();
	Schedule(const Schedule & other);
};