#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Section.hpp"
#include "Constraint.hpp"

class Department;

class Course
{
public:
	enum Status {PENDING, REFUSED, APPROVED, STATUSEND};
	Course(int departmentId, const std::string & courseCode, const std::string & courseName, const std::string & courseDescription, int numberOfCredits, Constraint * constraints);
	Course(int id, int departmentId, const std::string & courseCode, const std::string & courseName, const std::string & courseDescription, int numberOfCredits, Status status);

	int getID() const;
	std::string getCourseCode() const;
	std::string getCourseFullCode();
	std::string getCourseName() const;
	int getNumberOfCredits() const;

	void setDescription(std::string description);
	std::string getDescription() const;

	void setConstraint(Constraint* constraint);
	Constraint* getConstraint() const;

	bool addSection(Section* section);
	bool removeSection(Section* section);
	std::vector<Section*> getSections();

	int getDepartmentId() const;
	Department * getDepartment();

	Status getStatus() const;
	void approveCourse();
	void refuseCourse();

	~Course();

private:
	int mId;

	int mDepartmentID;
	Department* mDepartment;
	std::string mCourseCode; ///< Unique Course code

	std::string mCourseName; ///< Unique Course name
	std::string mDescription; ///< Descirption of the course
	int mNumberOfCredits; ///< number of credits of the course
	Status mStatus;

	Constraint* mConstraints; ///< constraints i.e: needComputers
	std::vector<int> mSectionIds; ///< vector of different section of the course
	std::vector<Section*> mSections; ///< vector of different section of the course
};

