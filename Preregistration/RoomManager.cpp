#include "RoomManager.h"

bool RoomManager::constraintChecker(Section * section, Room * room)
{
	if (section->getConstraint()->matchingConstraint(room->getConstraint()))
		return true;

	return false;
}

RoomManager * RoomManager::getInstance()
{
	if (sRoomManager == NULL)
		sRoomManager = new RoomManager();
	return sRoomManager;
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

vector<Room*> RoomManager::getRooms()
{
	return mRooms;
}

void RoomManager::assignRoom(Section * section)
{
	for (Room * room : getRooms())
	{
		if (constraintChecker(section, room))
		{
			section->setRoom(room);
			room->addSection(section);
			break;
		}
	}
}
