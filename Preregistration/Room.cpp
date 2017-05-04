#include "Room.h"
#include <algorithm>

const vector<Section *> Room ::getSections() const
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