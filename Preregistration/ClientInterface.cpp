#include "ClientInterface.hpp"

ClientInterface::ClientInterface() :client()
{
}

std::string ClientInterface::login(std::string params)
{
	params = "login" + ClientServerInterface::FUNC_DELIMITER + params;
	return client.sendData(params);	
}

std::string ClientInterface::getUsers(std::string params)
{
	return "";
}

void ClientInterface::addUser()
{
}

void ClientInterface::editUser()
{
}

void ClientInterface::deleteUser()
{
}

void ClientInterface::getMessages()
{
}

void ClientInterface::sendMessage()
{
}

void ClientInterface::getCourses()
{
}

void ClientInterface::addCourse()
{
}

void ClientInterface::deleteCourse()
{
}

void ClientInterface::getDepartments()
{
}

void ClientInterface::addDepartment()
{
}

void ClientInterface::editDepartment()
{
}

void ClientInterface::deleteDepartment()
{
}
