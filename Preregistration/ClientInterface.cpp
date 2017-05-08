#include "ClientInterface.hpp"

ClientInterface::ClientInterface() :client()
{
}

ClientInterface::~ClientInterface()
{
}

ClientInterface::ClientInterface(const ClientInterface & other)
{
}

ClientInterface & ClientInterface::operator=(const ClientInterface & rhs)
{
	// TODO: insert return statement here
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

std::string ClientInterface::deleteUser(std::string params)
{
	params = "deleteUser" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getMessages(std::string params)
{
	params = "getMessages" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::sendMessage(std::string params)
{
	params = "sendMessage" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getCourses(std::string params)
{
	params = "getCourses" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::addCourse(std::string params)
{
	params = "addCourse" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::deleteCourse(std::string params)
{
	params = "deleteCourse" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::getDepartments(std::string params)
{
	params = "getDepartments" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::addDepartment(std::string params)
{
	params = "addDepartment" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::editDepartment(std::string params)
{
	params = "editDepartment" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}

std::string ClientInterface::deleteDepartment(std::string params)
{
	params = "deleteDepartment" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);
}
