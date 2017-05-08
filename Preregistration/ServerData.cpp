#include "ServerData.hpp"
#include "Server.hpp"
#include "Helper.hpp"

ServerData::ServerData() : m_maxUserId(), m_maxUsername(), m_maxDepartmentId(-1)
{
	
}

ServerData::~ServerData()
{
	for (std::unordered_map<std::string, AbstractUser *>::iterator it = m_usersByUsername.begin(); it != m_usersByUsername.end(); ++it)
	{
		delete it->second;
	}

	for (std::unordered_map<int, Department *>::iterator it = m_departments.begin(); it != m_departments.end(); ++it)
	{
		delete it->second;
	}

	for (std::unordered_map<int, AbstractMessage *>::iterator it = m_messages.begin(); it != m_messages.end(); ++it)
	{
		delete it->second;
	}
	
	for (std::unordered_map<int, Course *>::iterator it = m_courses.begin(); it != m_courses.end(); ++it)
	{
		delete it->second;
	}

	for (std::unordered_map<int, Section *>::iterator it = m_sections.begin(); it != m_sections.end(); ++it)
	{
		delete it->second;
	}
}

Department * ServerData::getDepartment(int id) const
{
	std::unordered_map<int, Department*>::const_iterator it = m_departments.find(id);
	if (it != m_departments.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

AbstractUser * ServerData::getUser(std::string username) const
{
	std::unordered_map<std::string, AbstractUser*>::const_iterator it = m_usersByUsername.find(username);
	if (it != m_usersByUsername.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

AbstractUser * ServerData::getUser(int id) const
{
	std::unordered_map<int, AbstractUser*>::const_iterator it = m_usersById.find(id);
	if (it != m_usersById.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

AbstractMessage * ServerData::getMessage(int id) const
{
	std::unordered_map<int, AbstractMessage*>::const_iterator it = m_messages.find(id);
	if (it != m_messages.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

Course * ServerData::getCourse(int id) const
{
	std::unordered_map<int, Course*>::const_iterator it = m_courses.find(id);
	if (it != m_courses.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

Section * ServerData::getSection(int id) const
{
	std::unordered_map<int, Section*>::const_iterator it = m_sections.find(id);
	if (it != m_sections.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

bool ServerData::initialize()
{
	//TODO: check if there is an error
	getUsers();
	getDepartments();
	getMessages();
	getSections();
	getCourses();
	return true;
}

int ServerData::getNewUserId(int year)
{
	std::unordered_map<int, int>::iterator it = m_maxUserId.find(year);

	int newId;
	if (it == m_maxUserId.end()) {
		int maxId = year * 100000; // yyyy00000
		for (std::unordered_map<int, AbstractUser*>::const_iterator it = m_usersById.begin(); it != m_usersById.end(); ++it)
		{
			int id = it->first;
			if ((id > maxId) && (id / 100000 == year))
			{
				maxId = id;
			}
		}
		newId = maxId + 1;
	}
	else {
		newId = m_maxUserId[year] + 1;
	}
	m_maxUserId[year] = newId;
	return newId;
}

std::string ServerData::getNewUsername(std::string username)
{
	std::unordered_map<std::string, int>::iterator it = m_maxUsername.find(username);

	int newNumber;
	if (it == m_maxUsername.end())
	{ // if the map doesn't yet have abc, find the maximum number corresponding to abc
		int maxNumber = 0; //abc00
		for (std::unordered_map<std::string, AbstractUser*>::const_iterator it = m_usersByUsername.begin(); it != m_usersByUsername.end(); ++it)
		{
			std::string current = it->first;
			if (current.substr(0, 3) == username)
			{ // if current starts by username
				int number = Helper::stringToLong(current.substr(3, std::string::npos)); // get the number
				if (number > maxNumber) {
					maxNumber = number;
				}
			}
		}
		newNumber = maxNumber + 1;
	}
	else {
		newNumber = m_maxUsername[username] + 1;
	}

	m_maxUsername[username] = newNumber;

	std::string newUsername = username;
	if (newNumber < 10) {
		newUsername = newUsername + '0';
	}
	newUsername = newUsername + std::to_string(newNumber);

	return newUsername;
}

int ServerData::getNewDepartmentId() 
{
	int newId;
	if (m_maxDepartmentId == -1) {
		int maxId = m_departments.begin()->first;
		for (std::unordered_map<int, Department*>::const_iterator it = std::next(m_departments.begin(), 1); it != m_departments.end(); ++it)
		{
			int id = it->first;
			if (id > maxId)
			{
				maxId = id;
			}
		}
		newId = maxId + 1;
	}
	else {
		newId = m_maxDepartmentId + 1;
	}
	m_maxDepartmentId = newId;
	return newId;
}

std::vector<AbstractUser*> ServerData::getDepartmentUsers() const
{
	return std::vector<AbstractUser*>();
}

/**
* Retrieve departments from database.
*/
bool ServerData::getDepartments()
{
	std::vector<Department *> departments(Server::getInstance().repository->getDepartments());
	for (std::vector<Department*>::iterator it = departments.begin(); it != departments.end(); ++it)
	{
		Department * department = *it;
		m_departments[department->getId()] = department;
	}
	return true;
}

/**
* Retrieve users from the database.
*/
bool ServerData::getUsers()
{
	std::vector<AbstractUser*> users(Server::getInstance().repository->getUsers());
	for (std::vector<AbstractUser*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		AbstractUser * user = *it;
		m_usersById[user->getId()] = user;
		m_usersByUsername[user->getUsername()] = user;
	}
	return true;
}

/**
* Retrieve messages from database.
*/
bool ServerData::getMessages()
{
	std::vector<AbstractMessage *> messages(Server::getInstance().repository->getMessages());
	for (std::vector<AbstractMessage*>::iterator it = messages.begin(); it != messages.end(); ++it)
	{
		AbstractMessage * message = *it;
		m_messages[message->getId()] = message;

		message->getSender()->updateSentMessages(message);
		message->getRecipient()->updateReceivedMessages(message);
	}
	return true;
}

bool ServerData::getCourses()
{
	//TODO: implement
	return false;
}

bool ServerData::getSections()
{
	//TODO: implement
	return false;
}
