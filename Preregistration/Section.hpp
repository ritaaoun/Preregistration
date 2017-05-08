#pragma once
#include <vector>
#include <algorithm>
//#include "Professor.hpp"
#include "TimeSlot.h"
#include "Constraint.hpp"

class Professor;
class Room;

class Section
{
public:
	enum Status { Tentative, Definite, STATUS_END };

	bool addTimeSlot(TimeSlot* timeslot);
	bool removeTimeSlot(TimeSlot* timeslot);
	std::vector<TimeSlot*> getTimeSlots();

	void setStatus(Status status);
	Status getStatus();

	int getSectionCode();

	void setSectionCapacity(int capacity);
	int getSectionCapacity();

	void setRoom(Room* room);
	Room* getRoom();

	void setProfessor(Professor* professor);
	Professor* getProfessor();

	void setConstraint(Constraint * constraint);
	Constraint * getConstraint();


	Section(int input_sectionCode);
	Section(int input_id, int input_capacity, int input_courseID, int input_professorID, bool input_isConfirmed);
	~Section();

private:
	int mSectionCode; ///< section code
	int mCapacity; ///< section capacity
	int mCourseId; ///<  id of the course that the section gives
	int mProfId; ///<  id of the professor that teaches this section
	Room* mRoom; ///< Room used for the section
	Professor* mProfessor;
	Status mStatus; ///< section status
	std::vector<TimeSlot *> mTimeSlots; ///< time slots of the schedule of the section
	Constraint* mConstraints; ///< constraints i.e: needComputers
};

