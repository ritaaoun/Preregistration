#include "Room.h"
#include <algorithm>

const vector<Section *> Room ::getSections()
{
	return mSectionvector;
}

void Room::addSection(Section * section)
{
	vector<Section*>::iterator index = std::find(mSectionvector.begin(), mSectionvector.end(), section);
	if (index == mSectionvector.end())
	{
		mSectionvector.push_back(section);
	}
	
}

void Room::removeSection(Section * section)
{
	vector<Section*>::iterator index = std::find(mSectionvector.begin(), mSectionvector.end(), section);

	if (index != mSectionvector.end()) 
	{
		mSectionvector.erase(index);
	}
	
}

void Room::setConstraint(Constraint * constraint)
{
	mConstraints = constraint;
}

//Schedule* Room::getSchedule()
//{
//	mSchedule->generateSchedule();
//	return mSchedule;
//}

Constraint * Room::getConstraint()
{
	return mConstraints;
}

Room::Room(int input_capacity, std::string input_roomNumber, std::string input_buildingCode)
{
	capacity = input_capacity;
	roomNumber = input_roomNumber;
	buildingCode = input_buildingCode;
}

int Room::getCapacity()
{
	return capacity;
}

std::string Room::getRoomNumber()
{
	return roomNumber;
}

std::string Room::getBuildingCode()
{
	return buildingCode;
}
