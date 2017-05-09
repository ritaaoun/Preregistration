#pragma once
#include <unordered_map>
#include "AbstractUser.hpp"
#include "AbstractMessage.hpp"
#include "Course.hpp"
#include "Section.hpp"

class ServerData 
{
public:	
	ServerData();
	~ServerData();
	
	bool addDepartment(Department * department);
	Department * getDepartment(int id) const;

	bool addUser(AbstractUser * user);
	AbstractUser * getUser(std::string username) const;
	AbstractUser * getUser(int id) const;

	bool addMessage(AbstractMessage * message);
	AbstractMessage * getMessage(int id) const;

	bool addCourse(Course * course);
	Course * getCourse(int id) const;

	bool addSection(Section * section);
	Section * getSection(int crn) const;

	Room * getRoom(int id) const;

	bool initialize();

	int getNewUserId(int year);
	std::string getNewUsername(std::string username);
	int getNewSectionNumber(int courseId);

	std::vector<AbstractUser *> getDepartmentUsers(const Department * department) const;

private:
	std::unordered_map<std::string, AbstractUser *> m_usersByUsername;
	std::unordered_map<int, AbstractUser *> m_usersById;
	std::unordered_map<int, Department *> m_departments;
	std::unordered_map<int, AbstractMessage *> m_messages;
	std::unordered_map<int, Course *> m_courses;
	std::unordered_map<int, Section *> m_sections;
	std::unordered_map<int, Room *> m_rooms;

	std::unordered_map<int, int> m_maxUserId;
	std::unordered_map<std::string, int> m_maxUsername;
	std::unordered_map<int, int> m_maxSectionPerCourse;

	bool getDepartments();
	bool getUsers();
	bool getMessages();
	bool getCourses();
	bool getSections();
	bool getRooms();
};