#pragma once
#include "ClientServerInterface.hpp"
#include <string>
#include <unordered_map>


class ServerInterface : public ClientServerInterface
{
public:
	ServerInterface();
	~ServerInterface();
	ServerInterface(const ServerInterface & other);
	ServerInterface & operator=(const ServerInterface & rhs);

	typedef void(*pfunc)(std::string);

	std::unordered_map<std::string, pfunc> funcmap;

	std::string callFunction(std::string function);

	// Inherited via ClientServerInterface
	virtual void getUsers(std::string params) override;

	virtual void addUser() override;

	virtual void editUser() override;

	virtual void deleteUser() override;

	virtual void getMessages() override;

	virtual void sendMessage() override;

	virtual void getCourses() override;

	virtual void addCourse() override;

	virtual void deleteCourse() override;

	virtual void getDepartments() override;

	virtual void addDepartment() override;

	virtual void editDepartment() override;

	virtual void deleteDepartment() override;



};