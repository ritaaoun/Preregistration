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

	virtual  std::string getSentMessages(std::string params) override;

	virtual  std::string getReceivedMessages(std::string params) override;

	virtual  std::string sendMessage(std::string params) override;

	virtual  std::string getCourseRequests(std::string params) override;

	virtual  std::string getUserDepartmentCourses(std::string params) override;

	virtual  std::string addCourse(std::string params) override;

	virtual  std::string decideOnCourse(std::string params) override;

	virtual  std::string getDepartments(std::string params) override;

	virtual  std::string givePrivileges(std::string params) override;

	virtual  std::string getSections(std::string params) override;

	virtual  std::string getUserSections(std::string params) override;

	virtual std::string resetPassword(std::string params) override;

	virtual std::string changePassword(std::string params) override;

	virtual std::string addSection(std::string params) override;

	virtual std::string editSection(std::string params) override;

	virtual std::string deleteSection(std::string params) override;


	virtual std::string getUserDepartmentSections(std::string params) override;
private:

	typedef std::string(ServerInterface::*FnPtr)(std::string);
	std::map<std::string, FnPtr> functionMap;

};