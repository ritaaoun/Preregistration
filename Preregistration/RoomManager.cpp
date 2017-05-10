#include "RoomManager.h"

RoomManager::RoomManager()
{
}

bool RoomManager::constraintChecker(Section * section, Room * room)
{
	if (section->getConstraint()->matchingConstraint(room->getConstraint()))
		return true;

	return false;
}


RoomManager * RoomManager::getInstance()
{
	static RoomManager* instance(new RoomManager()); // Guaranteed to be destroyed.
	return instance;	// Instantiated on first use.		
}

void RoomManager::addRoom(Room * room)
{
	// check first if room is already in vector of rooms or not
	if (std::find(mRooms.begin(), mRooms.end(), room) == mRooms.end())
	{
		// if room not already in vector
		mRooms.push_back(room);
	}
}

void RoomManager::removeRoom(Room * room)
{

	// check first if room is already in vector of rooms or not
	if (std::find(mRooms.begin(), mRooms.end(), room) != mRooms.end())
	{
		mRooms.erase(std::remove(mRooms.begin(), mRooms.end(), room), mRooms.end());
	}
}

std::vector<Room*> RoomManager::getRooms()
{
	return mRooms;
}

void RoomManager::assignRoom(Section * section)
{
	for (Room * room : getRooms())
	{
		if (constraintChecker(section, room) && section->getCapacity() <= room->getCapacity())
		{
			section->setRoom(room);
			room->addSection(section);
			break;
		}
	}
}

