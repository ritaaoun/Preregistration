#pragma once
#include "ClientServerInterface.hpp"
#include "NetworkClient.hpp"

class ClientInterface : public ClientServerInterface
{
public:

	ClientInterface();
	~ClientInterface();
	ClientInterface(const ClientInterface & other);
	ClientInterface & operator=(const ClientInterface & rhs);

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
	virtual std::string confirmSection(const std::string & params) override;

private:
	NetworkClient client;

};