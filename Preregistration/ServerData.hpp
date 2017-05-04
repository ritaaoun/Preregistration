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
	
	Department * getDepartment(int id);
	AbstractUser * getUser(int id);
	AbstractMessage * getMessage(int id);
	Course * getCourse(int id);
	Section * getSection(int id);

	int getNewUserId(std::string year) const;
	std::string getNewUsername(std::string username) const;
	int getNewDepartmentId() const;

private:
	std::unordered_map<int, AbstractUser *> users;
	std::unordered_map<int, Department *> departments;
	std::unordered_map<int, AbstractMessage *> messages;
	std::unordered_map<int, Course *> courses;
	std::unordered_map<int, Section *> sections;

	bool getDepartments();
	bool getUsers();
	bool getMessages();
	bool getCourses();
	bool getSections();
};