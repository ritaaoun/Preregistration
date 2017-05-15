#include "ClientInterface.hpp"
#include <iostream>

ClientInterface::ClientInterface() : client()
{
}

ClientInterface::~ClientInterface()
{
}

ClientInterface::ClientInterface(const ClientInterface & other) : client(other.client)
{
}

ClientInterface & ClientInterface::operator=(const ClientInterface & rhs)
{
	client = rhs.client;
	return *this;
}

std::string ClientInterface::login(const std::string & params)
{
	std::string out = "login" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getUsers(const std::string & params)
{
	std::string out = "getUsers" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::addUser(const std::string & params)
{
	std::string out = "addUser" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::editUser(const std::string & params)
{
	std::string out = "editUser" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getSentMessages(const std::string & params)
{
	std::string out = "getSentMessages" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getReceivedMessages(const std::string & params)
{
	std::string out = "getReceivedMessages" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::sendMessage(const std::string & params)
{
	std::string out = "sendMessage" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getCourseRequests(const std::string & params)
{
	std::string out = "getCourseRequests" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getUserDepartmentCourses(const std::string & params)
{
	std::string out = "getUserDepartmentCourses" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::addCourse(const std::string & params)
{
	std::string out = "addCourse" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::decideOnCourse(const std::string & params)
{
	std::string out = "decideOnCourse" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getDepartments(const std::string & params)
{
	std::string out = "getDepartments" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::givePrivileges(const std::string & params)
{
	std::string out = "givePrivileges" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getSections(const std::string & params)
{
	std::string out = "getSections" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getUserSections(const std::string & params)
{
	std::string out = "getUserSections" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::resetPassword(const std::string & params)
{
	std::string out = "resetPassword" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::changePassword(const std::string & params)
{
	std::string out = "changePassword" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::publishSection(const std::string & params)
{
	std::string out = "publishSection" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::addSection(const std::string & params)
{
	std::string out = "addSection" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::editSection(const std::string & params)
{
	std::string out = "editSection" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::deleteSection(const std::string & params)
{
	std::string out = "deleteSection" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}

std::string ClientInterface::getUserDepartmentSections(const std::string & params)
{
	std::string out = "getUserDepartmentSections" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(out);
}
