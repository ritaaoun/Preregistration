#include "Course.hpp"
#include "Server.hpp"

Course::~Course()
{
	delete mConstraints;
}


Course::Course(int departmentId, const std::string & courseCode, const std::string & courseName, 
	const std::string & courseDescription, int numberOfCredits, Constraint * constraints) :
	mDepartmentID(departmentId), mDepartment(nullptr), mCode(courseCode), mName(courseName),
	mDescription(courseDescription), mNumberOfCredits(numberOfCredits), mStatus(PENDING), mConstraints(constraints),
	mSectionIds(), mSections()
{
	mId = Server::getInstance().repository->createCourse(this);
	Server::getInstance().data.addCourse(this);
}

Course::Course(int id, int departmentId, const std::string & courseCode, const std::string & courseName, 
	const std::string & courseDescription, int numberOfCredits, Status status) :
	mId(id), mDepartmentID(departmentId), mDepartment(nullptr), mCode(courseCode), mName(courseName),
	mDescription(courseDescription), mNumberOfCredits(numberOfCredits), mStatus(status),
	mConstraints(Server::getInstance().repository->getCourseConstraints(id)),
	mSectionIds(Server::getInstance().repository->getCourseSections(id)), mSections()
{
}

int Course::getID() const
{
	return mId;
}

std::string Course::getCode() const
{
	return mCode;
}

std::string Course::getFullCode()
{
	return getDepartment()->getCode() + mCode;
}

std::string Course::getName() const
{
	return mName;
}

int Course::getNumberOfCredits() const
{
	return mNumberOfCredits;
}

void Course::setDescription(std::string description)
{
	mDescription = description;
}

std::string Course::getDescription() const
{
	return mDescription;
}

void Course::setConstraint(Constraint * constraint)
{
	mConstraints = constraint;
}

Constraint * Course::getConstraint() const
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

std::vector<Section*> Course::getSections()
{
	if (mSections.empty() && !mSectionIds.empty())
	{
		for (std::vector<int>::iterator it = mSectionIds.begin(); it != mSectionIds.end(); ++it)
		{
			mSections.push_back(Server::getInstance().data.getSection(*it));
		}
	}
	return mSections;
}

int Course::getDepartmentId() const
{
	return mId;
}

Department * Course::getDepartment()
{
	if (mDepartment == nullptr)
	{
		mDepartment = Server::getInstance().data.getDepartment(mDepartmentID);
	}
	return mDepartment;
}

Course::Status Course::getStatus() const
{
	return mStatus;
}

void Course::approveCourse()
{
	mStatus = APPROVED;
	Server::getInstance().repository->updateCourse(this);
}

void Course::refuseCourse()
{
	mStatus = REFUSED;
	Server::getInstance().repository->updateCourse(this);
}

