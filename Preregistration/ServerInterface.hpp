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

	std::string callFunction(const std::string & function);

	// Inherited via ClientServerInterface
	virtual std::string login(const std::string & params) override;

	virtual std::string getUsers(const std::string & params) override;

	virtual  std::string addUser(const std::string & params) override;

	virtual  std::string editUser(const std::string & params) override;

	virtual  std::string getSentMessages(const std::string & params) override;

	virtual  std::string getReceivedMessages(const std::string & params) override;

	virtual  std::string sendMessage(const std::string & params) override;

	virtual  std::string getCourseRequests(const std::string & params) override;

	virtual  std::string getCourseSections(const std::string & params) override;

	virtual  std::string getUserDepartmentCourses(const std::string & params) override;

	virtual  std::string addCourse(const std::string & params) override;

	virtual  std::string decideOnCourse(const std::string & params) override;

	virtual  std::string getDepartments(const std::string & params) override;

	virtual  std::string givePrivileges(const std::string & params) override;

	virtual  std::string getSections(const std::string & params) override;

	virtual  std::string getUserSections(const std::string & params) override;

	virtual std::string resetPassword(const std::string & params) override;

	virtual std::string changePassword(const std::string & params) override;

	virtual  std::string publishSection(const std::string & params) override;

	virtual std::string addSection(const std::string & params) override;

	virtual std::string editSection(const std::string & params) override;

	virtual std::string deleteSection(const std::string & params) override;


	virtual std::string getUserDepartmentSections(const std::string & params) override;
private:

	typedef std::string(ServerInterface::*FnPtr)(const std::string &);
	std::map<std::string, FnPtr> functionMap;



};