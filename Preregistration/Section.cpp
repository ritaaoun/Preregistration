#include "Section.hpp"
#include "Server.hpp"

Section::Section(int input_sectionCode) :
mSectionCode (input_sectionCode)
{
}

Section::Section(int input_id, int input_capacity, int input_courseID, int input_professorID, bool input_isConfirmed) :
	mCapacity(input_capacity), mSectionCode(input_capacity), mCourseId(input_courseID), mProfId(input_professorID),
	mProfessor(nullptr), mStatus(static_cast<Status>(input_isConfirmed)), mRoom(nullptr), mTimeSlots(),
	mConstraints(Server::getInstance().repository->getSectionConstraint(input_id)), mCourse(nullptr)
{
	// use input_id to get contsraint of the section from database
	// build Constraint object from retreived 
}

Section::~Section()
{
	delete mConstraints;
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

Course * Section::getCourse()
{
	if (mCourse == nullptr)
	{
		mCourse = Server::getInstance().data.getCourse(mCourseId);
	}
	return mCourse;
}

