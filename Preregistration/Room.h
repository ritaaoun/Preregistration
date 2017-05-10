#pragma once

#include "Schedulable.h"
#include "Schedule.h"
#include "Section.hpp"
#include "Constraint.hpp"
#include <vector>

class Room : public Schedulable
{
public:
	Room(int id, const std::string & buildingCode, int roomNumber, int capacity);
	virtual ~Room();

	int getId() const;
	int getRoomNumber() const;
	std::string getBuildingCode() const;

	const std::vector<Section *> getSections() override;
	void addSection(Section* section);
	void removeSection(Section* section);

	void setConstraint(Constraint * constraint);
	Constraint* getConstraint() const;

	int getCapacity() const;
	void setCapacity(int capacity);

	Schedule * getSchedule();

private:
	int mId;
	std::string mBuildingCode; ///< building code, e.g. IOEC
	int  mRoomNumber; ///< room number, e.g. 243
	int mCapacity; ///< number of students that the room can handle
	Constraint* mConstraints; ///< constraints i.e: needComputers

	std::vector<int> mSectionIds;
	std::vector<Section*> mSections;
	Schedule* mSchedule;

	void loadSections();
};