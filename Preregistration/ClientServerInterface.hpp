#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "NetworkClient.hpp"

class ClientServerInterface
{
public:
	virtual std::string login(std::string params) = 0;
	virtual std::string getUsers(std::string params) = 0;
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

protected:
	std::vector<std::string> split(const std::string & s, std::string delim);
	static const std::string DELIMITER;
	static const std::string FUNC_DELIMITER;
};


