#pragma once
#include "ClientServerInterface.hpp"

class ClientInterface : public ClientServerInterface
{
	ClientInterface();
	~ClientInterface();
	ClientInterface(const ClientInterface & other);
	ClientInterface & operator=(const ClientInterface & rhs);

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