#pragma once
#include "AbstractUser.hpp"
#include "Department.hpp"
#include "Administrator.hpp"
#include "Room.h"
#include "AbstractMessage.hpp"
#include <vector>
#include <string>

class AbstractRepository
{
public:	
	virtual bool deleteUser(const AbstractUser * user) const = 0;
	virtual bool deleteUser(int id) const = 0;
	virtual bool updateUser(AbstractUser * user) const = 0;
	virtual bool createUser(const AbstractUser * user) const = 0;
	virtual std::vector<AbstractUser *> getUsers() const = 0;
	virtual std::vector<int> getUserSections(int userId) const = 0;

	virtual bool deleteDepartment(int id) const = 0;
	virtual bool deleteDepartment(const Department * department) const = 0;
	virtual bool updateDepartment(const Department * department) const = 0;
	virtual int createDepartment(const Department * department) const = 0;
	virtual std::vector<int> getAdminPrivileges(int adminId) const = 0;
	virtual std::vector<int> getDepartmentCourses(int departmentId) const = 0;
	virtual std::vector<int> getDepartmentCourseRequests(int departmentId) const = 0;
	virtual std::vector<Department *> getDepartments() const = 0;

	virtual bool deletePrivilege(const Administrator * admin, const Department * department) const = 0;
	virtual bool createPrivilege(const Administrator * admin, const Department * department) const = 0;

	virtual int createMessage(AbstractMessage * message) = 0;
	virtual std::vector<AbstractMessage *> getMessages() const = 0;

	virtual bool deleteSection(int crn) const = 0;
	virtual bool deleteSection(const Section * section) const = 0;
	virtual bool updateSection(const Section * section) const = 0;
	virtual int createSection(const Section * section) const = 0;
	virtual std::vector<Section*> getSections() const = 0;
	virtual std::vector<TimeSlot *> getSectionTimeSlots(int sectionCrn) const = 0;
	virtual bool updateSectionTimeSlots(Section * section) const = 0;
	virtual bool addStudentSection(Student * student, Section * section) const = 0;
	virtual bool removeStudentSection(Student * student, Section * section) const = 0;
	virtual bool addProfessorSection(Professor * professor, Section * section) const = 0;
	virtual bool removeProfessorSection(Professor * professor, Section * section) const = 0;
	virtual bool addRoomSection(Room * room, Section * section) const = 0;
	virtual bool removeRoomSection(Room * room, Section * section) const = 0;
	virtual std::vector<int> getSectionStudents(const Section * section) const = 0;

	virtual std::vector<Room*> getRooms() const = 0;
	virtual int getSectionRoomId(int sectionCrn) const = 0;
	virtual Constraint * getRoomConstraint(int roomId) const = 0;
	virtual std::vector<int> getRoomSectionIds(int roomId) const = 0;

	virtual bool deleteCourse(int id) const = 0;
	virtual bool deleteCourse(const Course * course) const = 0;
	virtual std::vector<Course *> getCourses() const = 0;
	virtual int createCourse(const Course * course) const = 0;
	virtual bool updateCourse(const Course * course) const = 0;
	virtual Constraint * getCourseConstraints(int courseId) const = 0;
	virtual std::vector<int> getCourseSections(int courseId) const = 0;
};
