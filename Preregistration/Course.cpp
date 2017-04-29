#include "Course.hpp"

Course::~Course()
{
}

Course::Course(const int input_courseCode, const std::string input_courseName, const int input_numberOfCredits)
{
	mCourseCode = input_courseCode;
	mCourseName = input_courseName;
	mNumberOfCredits = input_numberOfCredits;
}

int Course::getCourseCode()
{
	return mCourseCode;
}

std::string Course::getCourseName()
{
	return mCourseName;
}

int Course::getNumberOfCredits()
{
	return mNumberOfCredits;
}

void Course::setDescription(std::string description)
{
	mDescription = description;
}

std::string Course::getDescription()
{
	return mDescription;
}

void Course::setConstraint(Constraint * constraint)
{
	mConstraints = constraint;
}

Constraint * Course::getConstraint()
{
	return mConstraints;
}

bool Course::addSection(Section * section)
{
	// check first if section is already in vector of sections or not
	if (std::find(mSections.begin(), mSections.end(), section) == mSections.end())
	{
		// if section not already in vector
		section->setConstraint(this->getConstraint());
		mSections.push_back(section);
		return true;
	}
	return false;
}

bool Course::removeSection(Section * section)
{
	// check first if section is already in vector of sections or not
	if (std::find(mSections.begin(), mSections.end(), section) == mSections.end())
	{
		// if section not already in vector
		return false;
	}
	mSections.erase(std::remove(mSections.begin(), mSections.end(), section), mSections.end());
	return true;
}

