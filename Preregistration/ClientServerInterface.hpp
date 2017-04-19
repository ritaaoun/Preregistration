#pragma once
#include <string>

class ClientServerInterface
{
	virtual void getUsers(std::string params) = 0;
	virtual void addUser() = 0;
	virtual void editUser() = 0;
	virtual void deleteUser() = 0;

	virtual void getMessages() = 0;
	virtual void sendMessage() = 0;

	virtual void getCourses() = 0;
	virtual void addCourse() = 0;
	virtual void deleteCourse() = 0;

	virtual void getDepartments() = 0;
	virtual void addDepartment() = 0;
	virtual void editDepartment() = 0;
	virtual void deleteDepartment() = 0;

	//TODO: implement all functions needed by the client
};