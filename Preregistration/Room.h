#pragma once

#include "Schedulable.h"
#include "Schedule.h"
#include "Section.hpp"
#include "Constraint.hpp"
#include <list>

class Room : public Schedulable
{

private:
	std::list<Section*> mSectionList;
	Schedule* mSchedule;
	Constraint* mConstraints; ///< constraints i.e: needComputers


public:
	list<Section *> & getSections() const override;
	void addSection(Section* section);
	void removeSection(Section* section);
	void setConstraint(Constraint * constraint);
	//Schedule* getSchedule() override;
	Constraint* getConstraint();
};