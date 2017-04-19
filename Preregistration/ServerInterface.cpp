#include "ServerInterface.hpp"
#include "Server.hpp"

ServerInterface::ServerInterface()
{
	//funcmap["getUsers"] = &getUsers;
	//pfunc f = funcMap["getUsers"];
	//(*f)("");
}

std::string ServerInterface::callFunction(std::string function)
{
	return "hello";
}

void ServerInterface::getUsers(std::string params)
{
}

void ServerInterface::addUser()
{
}

void ServerInterface::editUser()
{
}

void ServerInterface::deleteUser()
{
}

void ServerInterface::getMessages()
{
}

void ServerInterface::sendMessage()
{
}

void ServerInterface::getCourses()
{
}

void ServerInterface::addCourse()
{
}

void ServerInterface::deleteCourse()
{
}

void ServerInterface::getDepartments()
{
}

void ServerInterface::addDepartment()
{
}

void ServerInterface::editDepartment()
{
}

void ServerInterface::deleteDepartment()
{
}


