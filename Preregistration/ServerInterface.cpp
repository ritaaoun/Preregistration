#include "ServerInterface.hpp"
#include "Server.hpp"
#include "Helper.hpp"
#include <functional>
#include <exception>

ServerInterface::ServerInterface()
{
	functionMap["login"] = &ServerInterface::login;
	functionMap["getUsers"] = &ServerInterface::getUsers;
	functionMap["addUser"] = &ServerInterface::addUser;
	functionMap["editUser"] = &ServerInterface::editUser;
	functionMap["getSentMessages"] = &ServerInterface::getSentMessages;
	functionMap["getReceivedMessages"] = &ServerInterface::getReceivedMessages;
	functionMap["sendMessage"] = &ServerInterface::sendMessage;
	functionMap["getCourses"] = &ServerInterface::getCourses;
	functionMap["addCourse"] = &ServerInterface::addCourse;
	functionMap["deleteCourse"] = &ServerInterface::deleteCourse;
	functionMap["getDepartments"] = &ServerInterface::getDepartments;

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
	std::string username = params;
	AbstractUser* user = Server::getInstance().data.getUser(username);
	if (user != nullptr)
	{
		if (user->getType() == AbstractUser::Type::ADMINISTRATOR)
		{
			Administrator * admin = (Administrator*)user;
			std::vector<AbstractUser*> users = admin->getUsers();
			std::string result = "";
			for (std::vector<AbstractUser*>::iterator it = users.begin();it != users.end();++it)
			{
				result += (*it)->getUsername() + ClientServerInterface::DELIMITER + std::to_string((*it)->getId()) +
					ClientServerInterface::DELIMITER + (*it)->getFirstName() + ClientServerInterface::DELIMITER + (*it)->getMiddleName() +
					ClientServerInterface::DELIMITER + (*it)->getLastName() + ClientServerInterface::DELIMITER +
					std::to_string((*it)->getType());
				if (users.end() != it + 1)
				{
					result += ClientServerInterface::LIST_DELIMITER;
				}
			}
			return result;
		}
	}

	return "false";
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
		std::string editedUsername = param[8];

		AbstractUser* user = Server::getInstance().data.getUser(username);
		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::ADMINISTRATOR)
			{
				Administrator * admin = (Administrator*)user;
				bool worked = admin->editUser(editedUsername, firstName, middleName, lastName, Helper::stringToLong(department), dateOfBirth);
				return std::to_string(worked);
			}
		}

		return "false";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::editUser" << e.what();
		return "false";
	}
}

std::string ServerInterface::getSentMessages(std::string params)
{
	try
	{
		AbstractUser* user = Server::getInstance().data.getUser(params);
		if (user != nullptr)
		{
			std::vector<AbstractMessage*> msgs = user->getSentMessages();
			std::string result = "";
			for (std::vector<AbstractMessage*>::iterator it = msgs.begin();it != msgs.end();++it)
			{
				result += (*it)->getSender()->getUsername() + ClientServerInterface::DELIMITER + (*it)->getRecipient()->getUsername() +
					ClientServerInterface::DELIMITER + (*it)->getTopic() + ClientServerInterface::DELIMITER + (*it)->getContent() +
					ClientServerInterface::DELIMITER + std::to_string((*it)->getType());
				if (msgs.end() != it + 1)
				{
					result += ClientServerInterface::LIST_DELIMITER;
				}
			}
			return result;
		}

		return "false";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::addUser" << e.what();
		return "false";
	}
}

std::string ServerInterface::getReceivedMessages(std::string params)
{
	try
	{
		AbstractUser* user = Server::getInstance().data.getUser(params);
		if (user != nullptr)
		{
			std::vector<AbstractMessage*> msgs = user->getReceivedMessages();
			std::string result = "";
			for (std::vector<AbstractMessage*>::iterator it = msgs.begin();it != msgs.end();++it)
			{
				result += (*it)->getSender()->getUsername() + ClientServerInterface::DELIMITER + (*it)->getRecipient()->getUsername() +
					ClientServerInterface::DELIMITER + (*it)->getTopic() + ClientServerInterface::DELIMITER + (*it)->getContent() +
					ClientServerInterface::DELIMITER + std::to_string((*it)->getType());
				if (msgs.end() != it + 1)
				{
					result += ClientServerInterface::LIST_DELIMITER;
				}
			}
			return result;
		}

		return "false";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::addUser" << e.what();
		return "false";
	}
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

