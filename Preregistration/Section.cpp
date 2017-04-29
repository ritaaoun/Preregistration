#include "Section.hpp"

Section::Section(int input_sectionCode)
{
	mSectionCode = input_sectionCode;
}

Section::~Section()
{
}

bool Section::addTimeSlot(TimeSlot * timeslot)
{
	// check first if section is already in vector of sections or not
	if (std::find(mTimeSlots.begin(), mTimeSlots.end(), timeslot) == mTimeSlots.end())
	{
		// if section not already in vector
		mTimeSlots.push_back(timeslot);
		return true;
	}
	return false;
}

bool Section::removeTimeSlot(TimeSlot * timeslot)
{
	// check first if section is already in vector of sections or not
	if (std::find(mTimeSlots.begin(), mTimeSlots.end(), timeslot) == mTimeSlots.end())
	{
		// if section not already in vector
		return false;
	}
	mTimeSlots.erase(std::remove(mTimeSlots.begin(), mTimeSlots.end(), timeslot), mTimeSlots.end());
	return true;
}

void Section::setStatus(Status status)
{
	mStatus = status;
}

Section::Status Section::getStatus()
{
	return mStatus;
}

int Section::getSectionCode()
{
	return mSectionCode;
}

void Section::setSectionCapacity(int capacity)
{
	mCapacity = capacity;
}

int Section::getSectionCapacity()
{
	return mCapacity;
}

void Section::setRoom(Room * room)
{
	mRoom = room;
}

Room * Section::getRoom()
{
	return mRoom;
}

void Section::setProfessor(Professor * professor)
{
	mProfessor = professor;
}

Professor * Section::getProfessor()
{
	return mProfessor;
}

std::vector<TimeSlot*> Section::getTimeSlots()
{
	return mTimeSlots;
}

void Section::setConstraint(Constraint * constraint)
{
	mConstraints = constraint;
}

Constraint * Section::getConstraint()
{
	return mConstraints;
}
