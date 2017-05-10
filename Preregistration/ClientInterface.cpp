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

std::string ClientInterface::login(std::string params)
{
	params = "login" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);	
}

std::string ClientInterface::getUsers(std::string params)
{
	params = "getUsers" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::addUser(std::string params)
{
	params = "addUser" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::editUser(std::string params)
{
	params = "editUser" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getSentMessages(std::string params)
{
	params = "getSentMessages" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getReceivedMessages(std::string params)
{
	params = "getReceivedMessages" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::sendMessage(std::string params)
{
	params = "sendMessage" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getCourseRequests(std::string params)
{
	params = "getCourseRequests" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getUserDepartmentCourses(std::string params)
{
	params = "getUserDepartmentCourses" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::addCourse(std::string params)
{
	params = "addCourse" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::decideOnCourse(std::string params)
{
	params = "decideOnCourse" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getDepartments(std::string params)
{
	params = "getDepartments" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::givePrivileges(std::string params)
{
	params = "givePrivileges" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getSections(std::string params)
{
	params = "getSections" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getUserSections(std::string params)
{
	params = "getUserSections" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::resetPassword(std::string params)
{
	params = "resetPassword" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::changePassword(std::string params)
{
	params = "changePassword" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::addSection(std::string params)
{
	params = "addSection" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::editSection(std::string params)
{
	params = "editSection" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::deleteSection(std::string params)
{
	params = "deleteSection" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getUserDepartmentSections(std::string params)
{
	params = "getUserDepartmentSections" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}
