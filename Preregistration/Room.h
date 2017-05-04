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


public:
	const vector<Section *> getSections() const override;
	void addSection(Section* section);
	void removeSection(Section* section);
	void setConstraint(Constraint * constraint);
	//Schedule* getSchedule() override;
	Constraint* getConstraint();
};