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
	Course(int departmentId, int input_courseCode, const std::string & input_courseName, int input_numberOfCredits);

	int getID() const;
	int getCourseCode();
	std::string getCourseName();
	int getNumberOfCredits();

	void setDescription(std::string description);
	std::string getDescription();

	void setConstraint(Constraint* constraint);
	Constraint* getConstraint();

	bool addSection(Section* section);
	bool removeSection(Section* section);

	Department * getDepartment();

	~Course();

private:
	int mId; 
	int mCourseCode; ///< Unique Course code
	std::string mCourseName; ///< Unique Course name
	std::string mDescription; ///< Descirption of the course
	std::vector<int> mSectionIds; ///< vector of different section of the course
	std::vector<Section*> mSections; ///< vector of different section of the course
	int mNumberOfCredits; ///< number of credits of the course
	Constraint* mConstraints; ///< constraints i.e: needComputers
	int mDepartmentID; 
	Department* mDepartment;
	
	// need to see how to store a departement depending on the implementation of the department i.e departmentId or departmentName or the department object ...
};

