#pragma once
#include <unordered_map>
#include "AbstractUser.hpp"

class ServerData 
{
	std::unordered_map<int, AbstractUser> users;
	std::unordered_map<int, Department> departments;
	
	bool getDepartments();
	bool getUsers();
};