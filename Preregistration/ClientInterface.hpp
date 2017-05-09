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
	virtual  std::string getCourses(std::string params) override;
	virtual  std::string addCourse(std::string params) override;
	virtual  std::string deleteCourse(std::string params) override;
	virtual  std::string getDepartments(std::string params) override;

private:
	NetworkClient client;
};