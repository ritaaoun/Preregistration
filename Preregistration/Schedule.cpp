#include "Schedule.h"

Schedule::Schedule(ISchedulable * schedulable) :
	mSchedulable(schedulable), mContainsConflict(false), mTimeSlots()
{
}

Schedule::~Schedule()
{
}

void Schedule::generateSchedule()
{
	mTimeSlots.clear();
	
	std::vector<Section*> sections = mSchedulable->getSections();

	for (unsigned int i = 0; i < sections.size(); ++i)
	{
		std::vector<TimeSlot*> sectionTimeSlots = sections.at(i)->getTimeSlots();

		for (unsigned int j = 0; j < sectionTimeSlots.size(); j++)
		{
			mContainsConflict = mContainsConflict || hasConflictWith(sectionTimeSlots.at(j));
			mTimeSlots.push_back(sectionTimeSlots.at(j));
		}
	}
}

bool Schedule::hasConflictWith(TimeSlot * timeSlot) const
{
	for (unsigned int i = 0; i < mTimeSlots.size(); i++)
	{
		TimeSlot* ts = mTimeSlots.at(i);

			/* 
				Conflicts are true when one of those 3 case are true:
				
				- ts.start < timeSlot.start < ts.end
				- ts.start < timeSlot.end < ts.end
				- timeSlot.start < ts.start < ts.end < timeSlot.end

				Since start and end are a combination of hours and minutes
				checking "ts.start < timeslot.start" for example is done this way:
				- ts.startHour <= timeslot.startHour && ts.startMinutes < timeSlot.startMinutes
			*/

			if (timeSlot->conflictsWith(ts))
			{
				return true;
			}
	}
	
	return false;
}

bool Schedule::hasConflictWith(std::vector<TimeSlot*> timeSlots) const
{
	for (unsigned int i = 0; i < timeSlots.size(); i++)
	{
		if (hasConflictWith(timeSlots.at(i)))
		{
			return true;
		}
	}
	return false;
}

bool Schedule::hasConflictWith(Section * section) const
{
	std::vector<TimeSlot*> sectionTimeSlots = section->getTimeSlots();

	return hasConflictWith(sectionTimeSlots);
}

bool Schedule::containsConflict() const
{
	return mContainsConflict;
}
