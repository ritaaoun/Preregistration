#pragma once

#include "Schedulable.h"
#include "TimeSlot.h"
#include "Section.hpp"

class Schedule {

private:
	Schedulable* mSchedulable;
	vector<TimeSlot*> mTimeSlots;
	bool mContainsConflict;

public:
	Schedule(Schedulable* schedulable);
	void generateSchedule();
	bool hasConflictWith(TimeSlot* timeSlot);
	bool hasConflictWith(vector<TimeSlot*> timeSlots);
	bool hasConflictWith(Section* section);
	bool containsConflict();
};