#pragma once
#include "ClientServerInterface.hpp"

class ClientInterface : public ClientServerInterface
{
public:

	ClientInterface();
	~ClientInterface();
	ClientInterface(const ClientInterface & other);
	ClientInterface & operator=(const ClientInterface & rhs);

	// Inherited via ClientServerInterface
	virtual std::string login(std::string params) override;
	virtual std::string getUsers(std::string params) override;
	virtual  std::string addUser(std::string params) override;
	virtual  std::string editUser(std::string params) override;
	virtual  std::string getSentMessages(std::string params) override;
	virtual  std::string getReceivedMessages(std::string params) override;
	virtual  std::string sendMessage(std::string params) override;
	virtual  std::string getCourseRequests(std::string params) override;
	virtual  std::string getUserCourses(std::string params) override;
	virtual  std::string addCourse(std::string params) override;
	virtual  std::string decideOnCourse(std::string params) override;
	virtual  std::string getDepartments(std::string params) override;
	virtual  std::string givePrivileges(std::string params) override;
	virtual  std::string getSections(std::string params) override;
	virtual  std::string getUserSections(std::string params) override;
	virtual std::string resetPassword(std::string params) override;
	virtual std::string changePassword(std::string params) override;

private:
	NetworkClient client;

};