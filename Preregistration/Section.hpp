#pragma once
#include <vector>
#include <algorithm>
#include "TimeSlot.h"
#include "Constraint.hpp"
#include "ISerializable.hpp"

class Professor;
class Room;
class Course;
class Student;

class Section : public ISerializable
{
public:
	enum Status { TENTATIVE, DEFINITE, STATUS_END };

	int getCrn() const;

	bool addTimeSlot(TimeSlot* timeslot);
	bool removeTimeSlot(TimeSlot* timeslot);
	bool setTimeSlots(const std::vector<TimeSlot*> & timeslots);
	std::vector<TimeSlot*> getTimeSlots() const;

	void setStatus(Status status);
	Status getStatus() const;

	int getNumber() const;

	void setCapacity(int capacity);
	int getCapacity() const;

	void setRoom(Room* room);
	Room* getRoom();
	int getRoomId() const;

	void setProfessor(Professor* professor);
	int getProfessorId() const;
	Professor* getProfessor();

	int getCourseId() const;
	Course * getCourse();

	std::vector<Student *> getStudents();
	int getNumberOfStudents() const;
	bool addStudent(Student * student);
	bool removeStudent(Student * student);

	bool confirm();
	
	// Inherited via ISerializable
	virtual std::string serialize() override;

	Section(int courseId, int capacity, int professorId, const std::vector < TimeSlot *> & timeSlots);
	Section(int crn, int courseId, int number, int capacity, int professorId, Status status);
	~Section();

private:
	int mCrn;

	int mCourseId; ///<  id of the course that the section gives
	Course* mCourse;
	int mSectionNumber; ///< section code

	int mCapacity; ///< section capacity

	int mProfId; ///<  id of the professor that teaches this section
	Professor* mProfessor;

	Status mStatus; ///< section status

	int mRoomId;
	Room* mRoom; ///< Room used for the section
	std::vector<TimeSlot *> mTimeSlots; ///< time slots of the schedule of the section

	std::vector<int> mStudentIds;
	std::vector<Student *> mStudents;

	void loadCourse();
	void loadProfessor();
	void loadRoom();
	void loadStudents();
};

