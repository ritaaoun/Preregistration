#pragma once
#include "ClientServerInterface.hpp"
#include <string>
#include <unordered_map>
#include <map>


class ServerInterface : public ClientServerInterface
{

public:
	ServerInterface();
	~ServerInterface();
	ServerInterface(const ServerInterface & other);
	ServerInterface & operator=(const ServerInterface & rhs);

	std::string callFunction(std::string function);

	// Inherited via ClientServerInterface
	virtual std::string login(std::string params) override;

	virtual std::string getUsers(std::string params) override;

	virtual  std::string addUser(std::string params) override;

	virtual  std::string editUser(std::string params) override;

	virtual  std::string deleteUser(std::string params) override;

	virtual  std::string getMessages(std::string params) override;

	virtual  std::string sendMessage(std::string params) override;

	virtual  std::string getCourses(std::string params) override;

	virtual  std::string addCourse(std::string params) override;

	virtual  std::string deleteCourse(std::string params) override;

	virtual  std::string getDepartments(std::string params) override;

	virtual  std::string addDepartment(std::string params) override;

	virtual  std::string editDepartment(std::string params) override;

	virtual  std::string deleteDepartment(std::string params) override;


private:

	typedef std::string(ServerInterface::*FnPtr)(std::string);
	std::map<std::string, FnPtr> functionMap;

};