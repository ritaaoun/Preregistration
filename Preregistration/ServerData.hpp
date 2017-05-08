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
	
	Department * getDepartment(int id) const;
	AbstractUser * getUser(std::string username) const;
	AbstractUser * getUser(int id) const;
	AbstractMessage * getMessage(int id) const;
	Course * getCourse(int id) const;
	Section * getSection(int id) const;

	bool initialize();

	int getNewUserId(int year);
	std::string getNewUsername(std::string username);
	int getNewDepartmentId();

	std::vector<AbstractUser *> getDepartmentUsers() const;

private:
	std::unordered_map<std::string, AbstractUser *> m_usersByUsername;
	std::unordered_map<int, AbstractUser *> m_usersById;
	std::unordered_map<int, Department *> m_departments;
	std::unordered_map<int, AbstractMessage *> m_messages;
	std::unordered_map<int, Course *> m_courses;
	std::unordered_map<int, Section *> m_sections;

	std::unordered_map<int, int> m_maxUserId;
	std::unordered_map<std::string, int> m_maxUsername;
	int m_maxDepartmentId;

	bool getDepartments();
	bool getUsers();
	bool getMessages();
	bool getCourses();
	bool getSections();
};