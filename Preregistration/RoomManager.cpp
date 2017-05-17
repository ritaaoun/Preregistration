#include "RoomManager.h"
#include "Course.hpp"

RoomManager::RoomManager() : mRoomIds(Server::getInstance().repository->getRoomIds()), mRooms()
{
}


RoomManager * RoomManager::getInstance()
{
	static RoomManager* instance(new RoomManager()); // Guaranteed to be destroyed.
	return instance;	// Instantiated on first use.		
}

void RoomManager::addRoom(Room * room)
{
	loadRooms();
	// check first if room is already in vector of rooms or not
	if (std::find(mRooms.begin(), mRooms.end(), room) == mRooms.end())
	{
		// if room not already in vector
		mRooms.push_back(room);
	}
}

void RoomManager::removeRoom(Room * room)
{
	loadRooms();
	// check first if room is already in vector of rooms or not
	if (std::find(mRooms.begin(), mRooms.end(), room) != mRooms.end())
	{
		mRooms.erase(std::remove(mRooms.begin(), mRooms.end(), room), mRooms.end());
	}
}

std::vector<Room*> RoomManager::getRooms()
{
	loadRooms();
	return mRooms;
}

bool RoomManager::assignRoom(Section * section)
{
	// Sort room accordig to capacity
	// This way the first room that fits the students and meets the constraints is selected
	loadRooms();

	for (Room * room : mRooms)
	{
		
		if (room->matchesConstraint(section->getCourse()) && section->getCapacity() <= room->getCapacity())
		{
			Schedule * schedule = room->getSchedule();
			bool hasConflicts = false;
			for (TimeSlot * timeslot : section->getTimeSlots())
				if (schedule->hasConflictWith(timeslot))
				{
					hasConflicts = true;
					break;
				}
			if (!hasConflicts)
			{
				section->setRoom(room);
				room->addSection(section);
				Server::getInstance().repository->addRoomSection(room, section);
				return true;
			}
		}
	}
	return false;
}

void RoomManager::loadRooms()
{
	if (mRooms.empty() && !mRoomIds.empty()) {
		for (std::vector<int>::const_iterator it = mRoomIds.begin(); it != mRoomIds.end(); ++it) {
			mRooms.push_back(Server::getInstance().data.getRoom(*it));
		}
		std::sort(mRooms.begin(), mRooms.end(), compareByCapacity);
		mRoomIds.clear();
		for (Room * room : mRooms)
			mRoomIds.push_back(room->getId());
	}
}

bool compareByCapacity(Room* a, Room* b)
{
	return a->getCapacity() < b->getCapacity();
}
