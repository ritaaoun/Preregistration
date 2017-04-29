#pragma once
#include <unordered_map>
#include "AbstractUser.hpp"
#include "AbstractMessage.hpp"

class ServerData 
{
public:	
	ServerData();
	
	Department * getDepartment(int id);
	AbstractUser * getUser(int id);
	AbstractMessage * getMessage(int id);

private:
	std::unordered_map<int, AbstractUser *> users;
	std::unordered_map<int, Department *> departments;
	std::unordered_map<int, AbstractMessage *> messages;

	bool getDepartments();
	bool getUsers();
	bool getMessages();
};