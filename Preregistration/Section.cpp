#include "Section.hpp"
#include "Server.hpp"
#include "Course.hpp"
#include "Professor.hpp"
#include "Student.hpp"

Section::~Section()
{
	delete mConstraints;

	for (std::vector<TimeSlot *>::iterator it = mTimeSlots.begin(); it != mTimeSlots.end(); ++it) {
		delete *it;
	}
}

void Section::loadCourse()
{
	if (mCourse == nullptr)
	{
		mCourse = Server::getInstance().data.getCourse(mCourseId);
	}
}

void Section::loadProfessor()
{
	if (mProfessor == nullptr) {
		mProfessor = static_cast<Professor *>(Server::getInstance().data.getUser(mProfId));
	}
}

void Section::loadRoom()
{
	if (mRoom == nullptr) {
		mRoom = Server::getInstance().data.getRoom(mRoomId);
	}
}

void Section::loadStudents()
{
	if (mStudents.empty() && !mStudentIds.empty()) {
		for (std::vector<int>::const_iterator it = mStudentIds.begin(); it != mStudentIds.end(); ++it) {
			mStudents.push_back(static_cast<Student*>(Server::getInstance().data.getUser(*it)));
		}
	}
}

int Section::getCrn() const
{
	return mCrn;
}

bool Section::addTimeSlot(TimeSlot * timeslot)
{
	// check first if section is already in vector of sections or not
	if (std::find(mTimeSlots.begin(), mTimeSlots.end(), timeslot) == mTimeSlots.end())
	{
		// if section not already in vector
		mTimeSlots.push_back(timeslot);
		return true;
	}
	return false;
}

bool Section::removeTimeSlot(TimeSlot * timeslot)
{
	// check first if section is already in vector of sections or not
	if (std::find(mTimeSlots.begin(), mTimeSlots.end(), timeslot) == mTimeSlots.end())
	{
		// if section not already in vector
		return false;
	}
	mTimeSlots.erase(std::remove(mTimeSlots.begin(), mTimeSlots.end(), timeslot), mTimeSlots.end());
	return true;
}

bool Section::setTimeSlots(const std::vector<TimeSlot*> & timeslots)
{
	for (std::vector<TimeSlot*>::iterator it = mTimeSlots.begin(); it != mTimeSlots.end(); ++it) {
		delete *it;
	}
	mTimeSlots = timeslots;
	return true;
}

void Section::setStatus(Status status)
{
	mStatus = status;
}

Section::Status Section::getStatus() const
{
	return mStatus;
}

int Section::getNumber() const
{
	return mSectionNumber;
}

void Section::setCapacity(int capacity)
{
	mCapacity = capacity;
}

int Section::getCapacity() const
{
	return mCapacity;
}

void Section::setRoom(Room * room)
{
	mRoomId = room->getId();
	mRoom = room;
}

int Section::getRoomId() const
{
	return mRoomId;
}

Room * Section::getRoom()
{
	loadRoom();
	return mRoom;
}

void Section::setProfessor(Professor * professor)
{
	mProfId = professor->getId();
	mProfessor = professor;
}

int Section::getProfessorId() const
{
	return mProfId;
}

Professor * Section::getProfessor()
{
	loadProfessor();
	return mProfessor;
}

std::vector<TimeSlot*> Section::getTimeSlots() const
{
	return mTimeSlots;
}

void Section::setConstraint(Constraint * constraint)
{
	mConstraints = constraint;
}

Constraint * Section::getConstraint()
{
	if (mConstraints == nullptr) {
		return getCourse()->getConstraint();
	}
	else {
		return mConstraints;
	}
}

int Section::getCourseId() const
{
	return mCourseId;
}

Course * Section::getCourse()
{
	loadCourse();
	return mCourse;
}

std::vector<Student*> Section::getStudents()
{
	loadStudents();
	return mStudents;
}

int Section::getNumberOfStudents() const
{
	return mStudentIds.size();
}

bool Section::addStudent(Student * student)
{
	loadStudents();
	mStudentIds.push_back(student->getId());
	mStudents.push_back(student);
	return true;
}

bool Section::removeStudent(Student * student)
{
	loadStudents();
	mStudentIds.erase(std::find(mStudentIds.begin(), mStudentIds.end(), student->getId()));
	mStudents.erase(std::find(mStudents.begin(), mStudents.end(), student));
	return true;
}

Section::Section(int courseId, int capacity, int professorId, const std::vector<TimeSlot*>& timeSlots) :
	mCourseId(courseId), mCourse(nullptr), mSectionNumber(Server::getInstance().data.getNewSectionNumber(courseId)),
	mCapacity(capacity), mProfId(professorId), mProfessor(nullptr), mStatus(TENTATIVE), mRoomId(-1), mRoom(nullptr),
	mTimeSlots(timeSlots), mConstraints(nullptr), mStudentIds(), mStudents()
{
	mCrn = Server::getInstance().repository->createSection(this);
	Server::getInstance().data.addSection(this);
}

Section::Section(int crn, int courseId, int number, int capacity, int professorId, Status status) :
	mCrn(crn), mCourseId(courseId), mCourse(nullptr), mSectionNumber(number), mCapacity(capacity), mProfId(professorId),
	mProfessor(nullptr), mStatus(status), mRoomId(Server::getInstance().repository->getSectionRoomId(crn)), mRoom(nullptr), 
	mTimeSlots(Server::getInstance().repository->getSectionTimeSlots(crn)), 
	mConstraints(Server::getInstance().repository->getSectionConstraint(crn)), 
	mStudentIds(Server::getInstance().repository->getSectionStudents(this)), mStudents()
{
}