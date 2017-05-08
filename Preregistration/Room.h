#pragma once

#include "Schedulable.h"
#include "Schedule.h"
#include "Section.hpp"
#include "Constraint.hpp"
#include <vector>

class Room : public Schedulable
{

private:
	std::vector<Section*> mSectionvector;
	Schedule* mSchedule;
	Constraint* mConstraints; ///< constraints i.e: needComputers
	std::string  roomNumber; ///< room number, e.g. 243
	std::string buildingCode; ///< building code, e.g. OXY
	int capacity; ///< number of students that the room can handle

public:
	const vector<Section *> getSections() override;
	void addSection(Section* section);
	void removeSection(Section* section);
	void setConstraint(Constraint * constraint);
	//Schedule* getSchedule() override;
	Constraint* getConstraint();
	Room(int input_capacity, std::string input_roomNumber, std::string input_buildingCode);
	int getCapacity();
	std::string getRoomNumber();
	std::string getBuildingCode();

};