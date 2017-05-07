#include "ServerInterface.hpp"
#include "Server.hpp"

ServerInterface::ServerInterface()
{
	//funcmap["getUsers"] = *getUsers;
	//pfunc f = funcMap["getUsers"];
	//(*f)("");
}

ServerInterface::~ServerInterface()
{
}

ServerInterface::ServerInterface(const ServerInterface & other)
{
}

ServerInterface & ServerInterface::operator=(const ServerInterface & rhs)
{
	// TODO: insert return statement here
	return *this;
}

std::string ServerInterface::callFunction(std::string function)
{
	std::vector<std::string> param = this->split(function, ClientServerInterface::FUNC_DELIMITER);
	return login(param[1]);

}

std::string ServerInterface::login(std::string params)
{
	std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

	std::string username = param[0];
	std::string password = param[1];
	AbstractUser* user = Server::getInstance().data.getUser(username);

	if (user != nullptr && user->checkPassword(password))
	{
		std::string userInfo = user->getUsername() + ClientServerInterface::DELIMITER + std::to_string(user->getId()) +
			ClientServerInterface::DELIMITER + user->getFirstName() + ClientServerInterface::DELIMITER + user->getMiddleName() +
			ClientServerInterface::DELIMITER + user->getLastName() + ClientServerInterface::DELIMITER +
			std::to_string(user->getType());
	}
	else
	{
		//return "false";
		//TODO: Chane to real impl

		return "caj07,:,201402911,:,christian,:,adel,:,jabr,:,2";
	}

}

std::string ServerInterface::getUsers(std::string params)
{
	//TODO: implement

	return "";
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
