#pragma once
#include "Room.h"
#include "Section.hpp"
#include "Server.hpp"
#include <vector>
#include <algorithm>

class RoomManager
{
private:
	RoomManager();
	std::vector<int> mRoomIds;
	std::vector<Room*> mRooms;

	//Constraint checker used when assigning rooms to sections
	bool constraintChecker(Course* course, Room* room);

public:
	static RoomManager* getInstance();

	void addRoom(Room* room);
	void removeRoom(Room* room);
	std::vector<Room*> getRooms();
	void assignRoom(Section* section);
	
	void loadRooms();
};
