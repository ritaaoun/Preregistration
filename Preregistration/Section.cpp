#include "Section.hpp"
#include "Server.hpp"
#include "Course.hpp"
#include "Professor.hpp"
#include "Student.hpp"
#include "RoomManager.h"
#include <iostream>

Section::~Section()
{
	for (std::vector<TimeSlot *>::iterator it = mTimeSlots.begin(); it != mTimeSlots.end(); ++it) {
		delete *it;
	}
}

void Section::loadCourse()
{
	if (mCourse == nullptr)
	{
		mCourse = Server::getInstance().data.getCourse(mCourseId);
	}
}

void Section::loadProfessor()
{
	if (mProfessor == nullptr) {
		mProfessor = static_cast<Professor *>(Server::getInstance().data.getUser(mProfId));
	}
}

void Section::loadRoom()
{
	if (mRoom == nullptr && mRoomId != -1) {
		mRoom = Server::getInstance().data.getRoom(mRoomId);
	}
}

void Section::loadStudents()
{
	if (mStudents.empty() && !mStudentIds.empty()) {
		for (std::vector<int>::const_iterator it = mStudentIds.begin(); it != mStudentIds.end(); ++it) {
			mStudents.push_back(static_cast<Student*>(Server::getInstance().data.getUser(*it)));
		}
	}
}

std::string Section::serialize()
{
	std::string result = std::to_string(getCrn()) + ClientServerInterface::DELIMITER + std::to_string(getCourseId()) +
		ClientServerInterface::DELIMITER + getCourse()->getFullCode() + ClientServerInterface::DELIMITER + getCourse()->getName() +
		ClientServerInterface::DELIMITER + getCourse()->getDescription() + ClientServerInterface::DELIMITER + std::to_string(getCourse()->getNumberOfCredits()) +
		ClientServerInterface::DELIMITER + std::to_string(getNumber()) +
		ClientServerInterface::DELIMITER + std::to_string(getCapacity()) + ClientServerInterface::DELIMITER +
		std::to_string(getNumberOfStudents()) + ClientServerInterface::DELIMITER + getProfessor()->getFullName();

	std::vector<TimeSlot*> slots = getTimeSlots();

	if (slots.size() > 0)
	{
		result += ClientServerInterface::DELIMITER;
		for (std::vector<TimeSlot*>::iterator it = slots.begin();it != slots.end();++it)
		{
			result += (*it)->serialize();
			if (slots.end() != it + 1)
			{
				result += ClientServerInterface::LIST_TIMESLOT_DELIMITER;
			}
		}
	} 
	
	result = result + ClientServerInterface::DELIMITER + std::to_string(mStatus) + ClientServerInterface::DELIMITER;

	loadRoom();
	if (mRoom == nullptr)
	{
		result = result + "TBA";
	}
	else
	{
		result = result + mRoom->getFullName();
	}

	return result;
}

int Section::getCrn() const
{
	return mCrn;
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

bool Section::setTimeSlots(const std::vector<TimeSlot*> & timeslots)
{
	for (std::vector<TimeSlot*>::iterator it = mTimeSlots.begin(); it != mTimeSlots.end(); ++it) {
		delete *it;
	}
	mTimeSlots = timeslots;
	return true;
}

void Section::setStatus(Status status)
{
	mStatus = status;
}

Section::Status Section::getStatus() const
{
	return mStatus;
}

int Section::getNumber() const
{
	return mSectionNumber;
}

void Section::setCapacity(int capacity)
{
	mCapacity = capacity;
}

int Section::getCapacity() const
{
	return mCapacity;
}

void Section::setRoom(Room * room)
{
	mRoomId = room->getId();
	mRoom = room;
	Server::getInstance().repository->setSectionRoomId(this, room);
}

int Section::getRoomId() const
{
	return mRoomId;
}

Room * Section::getRoom()
{
	loadRoom();
	return mRoom;
}

void Section::setProfessor(Professor * professor)
{
	mProfId = professor->getId();
	mProfessor = professor;
}

int Section::getProfessorId() const
{
	return mProfId;
}

Professor * Section::getProfessor()
{
	loadProfessor();
	return mProfessor;
}

std::vector<TimeSlot*> Section::getTimeSlots() const
{
	return mTimeSlots;
}

int Section::getCourseId() const
{
	return mCourseId;
}

Course * Section::getCourse()
{
	loadCourse();
	return mCourse;
}

std::vector<Student*> Section::getStudents()
{
	loadStudents();
	return mStudents;
}

int Section::getNumberOfStudents() const
{
	return (int)mStudentIds.size();
}

bool Section::addStudent(Student * student)
{
	loadStudents();
	mStudentIds.push_back(student->getId());
	mStudents.push_back(student);
	return true;
}

bool Section::removeStudent(Student * student)
{
	loadStudents();
	mStudentIds.erase(std::find(mStudentIds.begin(), mStudentIds.end(), student->getId()));
	mStudents.erase(std::find(mStudents.begin(), mStudents.end(), student));
	return true;
}

bool Section::confirm()
{
	if (mStatus == TENTATIVE)
	{
		if (RoomManager::getInstance()->assignRoom(this))
		{
			mStatus = DEFINITE;
			Server::getInstance().repository->updateSection(this);
			return true;
		}
		else
		{
			std::cout << "Section::confirm: There are no rooms currently available that match the time and capacity constraints of Section " <<
				mCrn << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Section::confirm: Section " << mCrn << " is already confirmed" << std::endl;
		return false;
	}
}

Section::Section(int courseId, int capacity, int professorId, const std::vector<TimeSlot*>& timeSlots) :
	mCourseId(courseId), mCourse(nullptr), mSectionNumber(Server::getInstance().data.getNewSectionNumber(courseId)),
	mCapacity(capacity), mProfId(professorId), mProfessor(nullptr), mStatus(TENTATIVE), mRoomId(-1), mRoom(nullptr),
	mTimeSlots(timeSlots), mStudentIds(), mStudents()
{
	mCrn = Server::getInstance().repository->createSection(this);
	Server::getInstance().repository->updateSectionTimeSlots(this);
	Server::getInstance().data.addSection(this);
}

Section::Section(int crn, int courseId, int number, int capacity, int professorId, Status status) :
	mCrn(crn), mCourseId(courseId), mCourse(nullptr), mSectionNumber(number), mCapacity(capacity), mProfId(professorId),
	mProfessor(nullptr), mStatus(status), mRoomId(Server::getInstance().repository->getSectionRoomId(crn)), mRoom(nullptr), 
	mTimeSlots(Server::getInstance().repository->getSectionTimeSlots(crn)),  
	mStudentIds(Server::getInstance().repository->getSectionStudents(this)), mStudents()
{
}