#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Section.hpp"
#include "Constraint.hpp"
#include "ISerializable.hpp"

class Department;

class Course : public ISerializable
{
public:
	enum Status { PENDING, REFUSED, APPROVED, STATUSEND };
	Course(int departmentId, const std::string & courseCode, const std::string & courseName, const std::string & courseDescription, int numberOfCredits, Constraint * constraints, int professorId);
	Course(int id, int departmentId, const std::string & courseCode, const std::string & courseName, const std::string & courseDescription, int numberOfCredits, Status status, int professorId);

	int getId() const;
	std::string getCode() const;
	std::string getFullCode();
	std::string getName() const;
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

	// Inherited via ISerializable
	virtual std::string serialize() override;

	int getProfessorId() const;
	Professor * getProfessor();

	~Course();

private:
	int mId;

	int mDepartmentID;
	Department* mDepartment;
	std::string mCode; ///< Unique Course code

	std::string mName; ///< Unique Course name
	std::string mDescription; ///< Descirption of the course
	int mNumberOfCredits; ///< number of credits of the course
	Status mStatus;

	Constraint* mConstraints; ///< constraints i.e: needComputers
	std::vector<int> mSectionIds; ///< vector of different section of the course
	std::vector<Section*> mSections; ///< vector of different section of the course

	int mProfessorId; ///< Id of professor who requested this course
	Professor * mProfessor;

	void loadDepartment();
	void loadSections();
	void loadProfessor();
};
