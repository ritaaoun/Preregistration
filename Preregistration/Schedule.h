#pragma once

#include "Schedulable.h"
#include "TimeSlot.h"
#include "Section.hpp"

class Schedule {
public:
	Schedule(Schedulable* schedulable);
	~Schedule();

	void generateSchedule();
	bool hasConflictWith(TimeSlot* timeSlot) const;
	bool hasConflictWith(std::vector<TimeSlot*> timeSlots) const;
	bool hasConflictWith(Section* section) const;
	bool containsConflict() const;

private:
	Schedulable* mSchedulable;
	std::vector<TimeSlot*> mTimeSlots;
	bool mContainsConflict;
	Schedule();
	Schedule(const Schedule & other);
};