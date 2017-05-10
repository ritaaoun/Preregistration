#include "ServerInterface.hpp"
#include "Server.hpp"
#include "Helper.hpp"
#include <functional>
#include <exception>
#include "Professor.hpp"

ServerInterface::ServerInterface()
{
	functionMap["login"] = &ServerInterface::login;
	functionMap["getUsers"] = &ServerInterface::getUsers;
	functionMap["addUser"] = &ServerInterface::addUser;
	functionMap["editUser"] = &ServerInterface::editUser;
	functionMap["getSentMessages"] = &ServerInterface::getSentMessages;
	functionMap["getReceivedMessages"] = &ServerInterface::getReceivedMessages;
	functionMap["sendMessage"] = &ServerInterface::sendMessage;
	functionMap["getCourseRequests"] = &ServerInterface::getCourseRequests;
	functionMap["addCourse"] = &ServerInterface::addCourse;
	functionMap["decideOnCourse"] = &ServerInterface::decideOnCourse;
	functionMap["getDepartments"] = &ServerInterface::getDepartments;
	functionMap["givePrivileges"] = &ServerInterface::givePrivileges;
	functionMap["getSections"] = &ServerInterface::getSections;
	functionMap["getUserSections"] = &ServerInterface::getUserSections;

}

ServerInterface::~ServerInterface()
{
}

ServerInterface::ServerInterface(const ServerInterface & other)
{
}

ServerInterface & ServerInterface::operator=(const ServerInterface & rhs)
{
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
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::login" << e.what() << std::endl;
		return "false";
	}

}

std::string ServerInterface::getUsers(std::string params)
{
	try {
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
					result += (*it)->getUsername() + ClientServerInterface::DELIMITER + (*it)->getFirstName() +
						ClientServerInterface::DELIMITER + (*it)->getMiddleName() + ClientServerInterface::DELIMITER +
						(*it)->getLastName() + ClientServerInterface::DELIMITER +
						std::to_string((*it)->getDepartmentId()) + ClientServerInterface::DELIMITER + (*it)->getBirthday() +
						ClientServerInterface::DELIMITER + std::to_string((*it)->getStartYear()) + ClientServerInterface::DELIMITER +
						std::to_string((*it)->getStartTerm()) + ClientServerInterface::DELIMITER + std::to_string((*it)->getType());
					if (users.end() != it + 1)
					{
						result += ClientServerInterface::LIST_DELIMITER;
					}
				}
				return result;
			}
		}

		return "";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getUsers" << e.what();
		return "";
	}
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
				return worked ? "true" : "false";
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

		return "";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getSentMessages" << e.what();
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

		return "";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getReceivedMessages" << e.what();
		return "";
	}
}

std::string ServerInterface::sendMessage(std::string params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param[0];
		std::string recipient = param[1];
		std::string topic = param[2];
		std::string content = param[3];

		AbstractUser* user = Server::getInstance().data.getUser(param[0]);
		if (user != nullptr)
		{
			bool sent = user->sendChatMessage(recipient, topic, content);
			return sent ? "true" : "false";
		}

		return "false";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::sendMessage" << e.what();
		return "false";
	}
}

std::string ServerInterface::getCourseRequests(std::string params)
{
	try
	{
		AbstractUser* user = Server::getInstance().data.getUser(params);

		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::ADMINISTRATOR)
			{
				Administrator * admin = (Administrator*)user;
				std::vector<Course*> courses = admin->getCourseRequests();
				std::string result = "";
				for (std::vector<Course*>::iterator it = courses.begin();it != courses.end();++it)
				{
					result += std::to_string((*it)->getID()) + ClientServerInterface::DELIMITER + (*it)->getCourseCode() + ClientServerInterface::DELIMITER +
						(*it)->getCourseName() + ClientServerInterface::DELIMITER + (*it)->getDescription() +
						ClientServerInterface::DELIMITER + std::to_string((*it)->getNumberOfCredits());

					if (courses.end() != it + 1)
					{
						result += ClientServerInterface::LIST_DELIMITER;
					}
				}
				return result;
			}
		}
		return "";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getCourseRequests" << e.what();
		return "";
	}
}

std::string ServerInterface::getUserCourses(std::string params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param[0];
		Course::Status status = (Course::Status)Helper::stringToLong(param[1]);

		std::vector<Course*> courses = Server::getInstance().data.getCourses(username, status);

		std::string result = "";
		for (std::vector<Course*>::iterator it = courses.begin();it != courses.end();++it)
		{
			result += std::to_string((*it)->getID()) + ClientServerInterface::DELIMITER + (*it)->getCourseCode() + ClientServerInterface::DELIMITER +
				(*it)->getCourseName() + ClientServerInterface::DELIMITER + (*it)->getDescription() +
				ClientServerInterface::DELIMITER + std::to_string((*it)->getNumberOfCredits());

			if (courses.end() != it + 1)
			{
				result += ClientServerInterface::LIST_DELIMITER;
			}
		}
		return result;

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getUserCourses" << e.what();
		return "";
	}
}

std::string ServerInterface::addCourse(std::string params)
{
	try {
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param[0];
		std::string departmentId = param[1];
		std::string courseCode = param[1];
		std::string courseName = param[1];
		std::string description = param[1];
		std::string credits = param[1];
		bool computer = Helper::stringToLong(param[1]) == 1;
		bool speaker = Helper::stringToLong(param[1]) == 1;
		bool accelerator = Helper::stringToLong(param[1]) == 1;

		AbstractUser* user = Server::getInstance().data.getUser(username);
		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::PROFESSOR)
			{
				Professor * prof = (Professor*)user;

				Constraint * constraint = new Constraint(computer, speaker, accelerator);
				bool success = prof->requestCourse(Helper::stringToLong(departmentId), courseCode, courseName, description,
					Helper::stringToLong(credits), constraint);

				return success ? "true" : "false";
			}
		}

		return "false";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::addCourse" << e.what();
		return "false";
	}
}

std::string ServerInterface::decideOnCourse(std::string params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param[0];
		std::string courseId = param[1];
		std::string status = param[2];

		AbstractUser* user = Server::getInstance().data.getUser(username);
		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::ADMINISTRATOR)
			{
				Administrator * admin = (Administrator*)user;
				Course * course = Server::getInstance().data.getCourse(Helper::stringToLong(courseId));
				bool success = admin->decideOnCourse(course, status == "1");
				return success ? "true" : "false";
			}
		}

		return "false";

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::decideOnCourse" << e.what();
		return "false";
	}
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
		return "";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getDepartments" << e.what();
		return "false";
	}
}

std::string ServerInterface::givePrivileges(std::string params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param[0];
		std::string recipient = param[1];
		int departmentId = Helper::stringToLong(param[2]);

		std::string result = "";
		AbstractUser* user = Server::getInstance().data.getUser(param[0]);
		AbstractUser* recip = Server::getInstance().data.getUser(param[1]);
		Department* department = Server::getInstance().data.getDepartment(departmentId);

		if (user != nullptr && recip != nullptr && department != nullptr)
		{
			if (user->getType() == AbstractUser::Type::ADMINISTRATOR)
			{
				Administrator * admin = (Administrator*)user;

				bool success = admin->givePrivilege((Administrator*)recip, department);

				return success ? "true" : "false";
			}
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::givePrivileges" << e.what();
		return "false";
	}
}

std::string ServerInterface::getSections(std::string params)
{
	return std::string();
}

std::string ServerInterface::getUserSections(std::string params)
{
	return std::string();
}

