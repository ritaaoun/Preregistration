#include "ServerData.hpp"

ServerData::ServerData()
{
}

Department * ServerData::getDepartment(int id)
{
	return nullptr;
}

AbstractUser * ServerData::getUser(int id)
{
	return nullptr;
}

AbstractMessage * ServerData::getMessage(int id)
{
	return nullptr;
}

Course * ServerData::getCourse(int id)
{
	return nullptr;
}

Section * ServerData::getSection(int id)
{
	return nullptr;
}

int ServerData::getNewUserId(std::string year) const
{
	return 0;
}

std::string ServerData::getNewUsername(std::string username) const
{
	return std::string();
}

int ServerData::getNewDepartmentId() const
{
	return 0;
}

bool ServerData::getDepartments()
{
	return false;
}

bool ServerData::getUsers()
{
	return false;
}

bool ServerData::getMessages()
{
	return false;
}

bool ServerData::getCourses()
{
	return false;
}

bool ServerData::getSections()
{
	return false;
}
