#include "ServerInterface.hpp"
#include "Server.hpp"
#include <functional>
#include <exception>

ServerInterface::ServerInterface()
{
	functionMap["login"] = &ServerInterface::login;
	functionMap["getUsers"] = &ServerInterface::getUsers;
	functionMap["addUser"] = &ServerInterface::addUser;
	functionMap["editUser"] = &ServerInterface::editUser;
	functionMap["deleteUser"] = &ServerInterface::deleteUser;
	functionMap["getMessages"] = &ServerInterface::getMessages;
	functionMap["sendMessage"] = &ServerInterface::sendMessage;
	functionMap["getCourses"] = &ServerInterface::getCourses;
	functionMap["addCourse"] = &ServerInterface::addCourse;
	functionMap["deleteCourse"] = &ServerInterface::deleteCourse;
	functionMap["getDepartments"] = &ServerInterface::getDepartments;
	functionMap["addDepartment"] = &ServerInterface::addDepartment;
	functionMap["editDepartment"] = &ServerInterface::editDepartment;
	functionMap["deleteDepartment"] = &ServerInterface::deleteDepartment;

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
	try
	{
		std::vector<std::string> param = this->split(function, ClientServerInterface::FUNC_DELIMITER);
		FnPtr p = functionMap[param[0]];
		if (p != nullptr)
		{
			return (this->*p)(param[1]);
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::login" << e.what();
		return "false";
	}
}

std::string ServerInterface::login(std::string params)
{
	try {
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
			return userInfo;
		}

		return "false";
		//TODO: Chane to real impl

		//return "caj07,:,201402911,:,christian,:,adel,:,jabr,:,2";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::login" << e.what();
		return "false";
	}

}

std::string ServerInterface::getUsers(std::string params)
{
	//std::vector<AbstractUser*> user = Server::getInstance().data.getUser(params);

	return "";
}

std::string ServerInterface::addUser(std::string params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param[0];
		std::string firstName = param[1];
		std::string middleName = param[2];
		std::string lastName = param[3];
		std::string department = param[4];
		std::string dateOfBirth = param[5];
		std::string startYear = param[6];
		std::string startTerm = param[7];
		std::string userType = param[8];

		AbstractUser* user = Server::getInstance().data.getUser(username);
		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::ADMINISTRATOR)
			{
				Administrator * admin = (Administrator*)user;
				AbstractUser* createdUser = admin->createUser(firstName, middleName, lastName, std::stoi(startYear), (Term::Term)std::stoi(startTerm),
					(AbstractUser::Type)std::stoi(userType), std::stoi(department), dateOfBirth);
				if (createdUser != nullptr)
				{
					return "true";
				}
			}
		}

		return "false";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::addUser" << e.what();
		return "false";
	}
}

std::string ServerInterface::editUser(std::string params)
{
	return "";
}

std::string ServerInterface::deleteUser(std::string params)
{
	return "";
}

std::string ServerInterface::getMessages(std::string params)
{
	return "";
}

std::string ServerInterface::sendMessage(std::string params)
{
	return "";
}

std::string ServerInterface::getCourses(std::string params)
{
	return "";
}

std::string ServerInterface::addCourse(std::string params)
{
	return "";
}

std::string ServerInterface::deleteCourse(std::string params)
{
	return "";
}

std::string ServerInterface::getDepartments(std::string params)
{
	try
	{
		std::string result = "";
		AbstractUser* user = Server::getInstance().data.getUser(params);
		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::ADMINISTRATOR)
			{
				Administrator * admin = (Administrator*)user;

				std::vector<Department*> deps = admin->getPrivileges();
				for (std::vector<Department*>::iterator it = deps.begin();it != deps.end();++it)
				{
					result += std::to_string((*it)->getId()) + ClientServerInterface::DELIMITER + (*it)->getName();
					if (deps.end() != it + 1)
					{
						result += ClientServerInterface::LIST_DELIMITER;
					}
				}
				return result;
			}
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getDepartments" << e.what();
		return "false";
	}
}

std::string ServerInterface::addDepartment(std::string params)
{
	return "";
}

std::string ServerInterface::editDepartment(std::string params)
{
	return "";
}

std::string ServerInterface::deleteDepartment(std::string params)
{
	return "";
}
