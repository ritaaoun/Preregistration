#include "Course.hpp"
#include "Server.hpp"

Course::~Course()
{
	delete mConstraints;
}

void Course::loadDepartment()
{
	if (mDepartment == nullptr) {
		mDepartment = Server::getInstance().data.getDepartment(mDepartmentID);
	}
}

void Course::loadSections()
{
	if (mSections.empty() && !mSectionIds.empty()) {
		for (std::vector<int>::iterator it = mSectionIds.begin(); it != mSectionIds.end(); ++it)
		{
			mSections.push_back(Server::getInstance().data.getSection(*it));
		}
	}
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
	loadDepartment();
	return mDepartment->getCode() + mCode;
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
		loadSections();
		mSectionIds.push_back(section->getCrn());
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
		std::cerr << "Course::removeSection: Section " << section->getCrn() << " does not belong to course " << mId << std::endl;
		return false;
	}
	std::cout << "Course::removeSection: Section " << section->getCrn() << " has been added to course " << mId << std::endl;
	mSections.erase(std::remove(mSections.begin(), mSections.end(), section), mSections.end());
	return true;
}

std::vector<Section*> Course::getSections()
{
	loadSections();
	return mSections;
}

int Course::getDepartmentId() const
{
	return mId;
}

Department * Course::getDepartment()
{
	loadDepartment();
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

