#include "Course.hpp"
#include "Server.hpp"
#include "Professor.hpp"
#include <iostream>

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

void Course::loadProfessor()
{
	if (mProfessor == nullptr) {
		mProfessor = static_cast<Professor*>(Server::getInstance().data.getUser(mProfessorId));
	}
}
std::string Course::serialize()
{
	return std::to_string(getId()) + ClientServerInterface::DELIMITER + getFullCode() + ClientServerInterface::DELIMITER +
		getName() + ClientServerInterface::DELIMITER + getDescription() +
		ClientServerInterface::DELIMITER + std::to_string(getNumberOfCredits());
}



Course::Course(int departmentId, const std::string & courseCode, const std::string & courseName, 
	const std::string & courseDescription, int numberOfCredits, Constraint * constraints, int professorId) :
	mDepartmentID(departmentId), mDepartment(nullptr), mCode(courseCode), mName(courseName),
	mDescription(courseDescription), mNumberOfCredits(numberOfCredits), mStatus(PENDING), mConstraints(constraints),
	mSectionIds(), mSections(), mProfessorId(professorId), mProfessor(nullptr)
{
	mId = Server::getInstance().repository->createCourse(this);
	Server::getInstance().data.addCourse(this);
}

Course::Course(int id, int departmentId, const std::string & courseCode, const std::string & courseName, 
	const std::string & courseDescription, int numberOfCredits, Status status, int professorId) :
	mId(id), mDepartmentID(departmentId), mDepartment(nullptr), mCode(courseCode), mName(courseName),
	mDescription(courseDescription), mNumberOfCredits(numberOfCredits), mStatus(status),
	mConstraints(Server::getInstance().repository->getCourseConstraints(id)),
	mSectionIds(Server::getInstance().repository->getCourseSections(id)), mSections(), mProfessorId(professorId),
	mProfessor(nullptr)
{
}

int Course::getId() const
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
	std::cout << "Course::removeSection: Section " << section->getCrn() << " has been removed from the course " << mId << std::endl;
	mSections.erase(std::remove(mSections.begin(), mSections.end(), section), mSections.end());
	mSectionIds.erase(std::remove(mSectionIds.begin(), mSectionIds.end(), section->getCrn()), mSectionIds.end());
	return true;
}

std::vector<Section*> Course::getSections()
{
	loadSections();
	return mSections;
}

int Course::getDepartmentId() const
{
	return mDepartmentID;
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

int Course::getProfessorId() const
{
	return mProfessorId;
}

Professor * Course::getProfessor()
{
	loadProfessor();
	return mProfessor;
}

