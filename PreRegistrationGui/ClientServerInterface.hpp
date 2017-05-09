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
	virtual  std::string addUser(std::string params) = 0;
	virtual  std::string editUser(std::string params) = 0;
	virtual  std::string deleteUser(std::string params) = 0;

	virtual  std::string getMessages(std::string params) = 0;
	virtual  std::string sendMessage(std::string params) = 0;

	virtual  std::string getCourses(std::string params) = 0;
	virtual  std::string addCourse(std::string params) = 0;
	virtual  std::string deleteCourse(std::string params) = 0;

	virtual  std::string getDepartments(std::string params) = 0;
	virtual  std::string addDepartment(std::string params) = 0;
	virtual  std::string editDepartment(std::string params) = 0;
	virtual  std::string deleteDepartment(std::string params) = 0;


	static std::vector<std::string> split(const std::string & s, std::string delim);
	static const std::string DELIMITER;
	static const std::string FUNC_DELIMITER;
	static const std::string LIST_DELIMITER;
};


