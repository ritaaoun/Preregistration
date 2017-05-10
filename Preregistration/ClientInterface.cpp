#include "ClientInterface.hpp"

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
	params = "getCourses" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getUserCourses(std::string params)
{
	params = "getUserCourses" + ClientServerInterface::FUNC_DELIMITER + params;
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
