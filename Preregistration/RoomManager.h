#pragma once
#include "Room.h"
#include "Section.hpp"
#include <vector>
#include <algorithm>

class RoomManager
{
private:
	RoomManager();
	std::vector<Room*> mRooms;

	//Constraint checker used when assigning rooms to sections
	bool constraintChecker(Section* section, Room* room);

public:
	static RoomManager* getInstance();

	void addRoom(Room* room);
	void removeRoom(Room* room);
	std::vector<Room*> getRooms();
	void assignRoom(Section* section);
};
