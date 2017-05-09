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

int Room::getId() const
{
	return mId;
}

const vector<Section *> Room ::getSections()
{
	if (mSections.empty() && !mSectionIds.empty()) {
		for (std::vector<int>::const_iterator it = mSectionIds.begin(); it != mSectionIds.end(); ++it) {
			mSections.push_back(Server::getInstance().data.getSection(*it));
		}
	}
	return mSections;
}

void Room::addSection(Section * section)
{
	getSections();
	vector<Section*>::iterator index = std::find(mSections.begin(), mSections.end(), section);
	if (index == mSections.end())
	{
		mSections.push_back(section);
	}
	
}

void Room::removeSection(Section * section)
{
	getSections();
	vector<Section*>::iterator index = std::find(mSections.begin(), mSections.end(), section);

	if (index != mSections.end())
	{
		mSections.erase(index);
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
