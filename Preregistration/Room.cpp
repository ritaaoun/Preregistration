#include "Room.h"
#include "Server.hpp"
#include <algorithm>

Room::Room(int id, const std::string & buildingCode, int roomNumber, int capacity) :
	mId(id), mBuildingCode(buildingCode), mRoomNumber(roomNumber), mCapacity(capacity),
	mConstraints(Server::getInstance().repository->getRoomConstraint(id)), 
	mSectionIds(Server::getInstance().repository->getRoomSectionIds(id)), mSections(),
	mSchedule(new Schedule(this))
{
}

Room::~Room()
{
	if (mConstraints != nullptr) {
		delete mConstraints;
	}
	delete mSchedule;
}

Room & Room::operator=(const Room & rhs)
{
	mId = rhs.mId;
	mBuildingCode = rhs.mBuildingCode;
	mRoomNumber = rhs.mRoomNumber;
	mCapacity = rhs.mCapacity;
	mConstraints = rhs.mConstraints;
	mSectionIds = rhs.mSectionIds;
	mSections = rhs.mSections;
	return *this;
}

bool Room::operator < (const Room& rhs) const
{
	return (mCapacity < rhs.mCapacity);
}

int Room::getId() const
{
	return mId;
}

const std::vector<Section *> Room ::getSections()
{
	loadSections();
	return mSections;
}

void Room::addSection(Section * section)
{
	if (section->getRoom() == nullptr)
	{
		loadSections();
		mSectionIds.push_back(section->getCrn());
		mSections.push_back(section);
		Server::getInstance().repository->addRoomSection(this, section);
	}
	
}

void Room::removeSection(Section * section)
{
	if (section->getRoom() == this)
	{
		loadSections();
		mSectionIds.erase(std::remove(mSectionIds.begin(), mSectionIds.end(), section->getCrn()), mSectionIds.end());
		mSections.erase(std::remove(mSections.begin(), mSections.end(), section), mSections.end());
		Server::getInstance().repository->removeRoomSection(this, section);
	}
	
}

void Room::setConstraint(Constraint * constraint)
{
	if (mConstraints != nullptr) {
		delete mConstraints;
	}
	mConstraints = constraint;
}

Schedule* Room::getSchedule()
{
	mSchedule->generateSchedule();
	return mSchedule;
}

std::string Room::serialize()
{
	return std::string();
}

bool Room::matchesConstraint(Course * course)
{
	Constraint* courseConstraints = course->getConstraint();

	if (courseConstraints->hasComputer() && !mConstraints->hasComputer())
		return false;

	if (courseConstraints->hasSpeakers() && !mConstraints->hasSpeakers())
		return false;

	if (courseConstraints->HasHighEnergyParticleAccelerator() && !mConstraints->HasHighEnergyParticleAccelerator())
		return false;

	return true;
}

void Room::loadSections()
{
	if (mSections.empty() && !mSectionIds.empty()) {
		for (std::vector<int>::const_iterator it = mSectionIds.begin(); it != mSectionIds.end(); ++it) {
			mSections.push_back(Server::getInstance().data.getSection(*it));
		}
	}
}

Constraint * Room::getConstraint() const
{
	return mConstraints;
}

int Room::getCapacity() const
{
	return mCapacity;
}

void Room::setCapacity(int capacity)
{
	mCapacity = capacity;
}

int Room::getRoomNumber() const
{
	return mRoomNumber;
}

std::string Room::getBuildingCode() const
{
	return mBuildingCode;
}
