#include "ServerInterface.hpp"
#include "Server.hpp"
#include "Helper.hpp"
#include <functional>
#include <exception>
#include "Professor.hpp"
#include "Student.hpp"
#include "Section.hpp"
#include "Course.hpp"
#include<iostream>

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
	functionMap["getCourseSections"] = &ServerInterface::getCourseSections;
	functionMap["getUserDepartmentCourses"] = &ServerInterface::getUserDepartmentCourses;
	functionMap["addCourse"] = &ServerInterface::addCourse;
	functionMap["publishSection"] = &ServerInterface::publishSection;
	functionMap["decideOnCourse"] = &ServerInterface::decideOnCourse;
	functionMap["getDepartments"] = &ServerInterface::getDepartments;
	functionMap["givePrivileges"] = &ServerInterface::givePrivileges;
	functionMap["getSections"] = &ServerInterface::getSections;
	functionMap["resetPassword"] = &ServerInterface::resetPassword;
	functionMap["changePassword"] = &ServerInterface::changePassword;
	functionMap["getUserSections"] = &ServerInterface::getUserSections;
	functionMap["addSection"] = &ServerInterface::addSection;
	functionMap["editSection"] = &ServerInterface::editSection;
	functionMap["deleteSection"] = &ServerInterface::deleteSection;
	functionMap["getUserDepartmentSections"] = &ServerInterface::getUserDepartmentSections;

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

std::string ServerInterface::callFunction(const std::string & function)
{
	try
	{
		std::vector<std::string> param = this->split(function, ClientServerInterface::FUNC_DELIMITER);
		FnPtr p = functionMap[param.at(0)];
		if (p != nullptr)
		{
			return (this->*p)(param.at(1));
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::login" << e.what();
		return "false";
	}
}

std::string ServerInterface::login(const std::string & params)
{
	try {
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string password = param.at(1);
		AbstractUser* user = Server::getInstance().data.getUser(username);

		if (user != nullptr && user->checkPassword(password))
		{
			return user->serialize();
		}

		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::login" << e.what() << std::endl;
		return "false";
	}

}

std::string ServerInterface::getUsers(const std::string & params)
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
					result += (*it)->serialize();
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

std::string ServerInterface::addUser(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string firstName = param.at(1);
		std::string middleName = param.at(2);
		std::string lastName = param.at(3);
		std::string department = param.at(4);
		std::string dateOfBirth = param.at(5);
		std::string startYear = param.at(6);
		std::string startTerm = param.at(7);
		std::string userType = param.at(8);

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

std::string ServerInterface::editUser(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string firstName = param.at(1);
		std::string middleName = param.at(2);
		std::string lastName = param.at(3);
		std::string department = param.at(4);
		std::string dateOfBirth = param.at(5);
		std::string startYear = param.at(6);
		std::string startTerm = param.at(7);
		std::string editedUsername = param.at(8);

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

std::string ServerInterface::getSentMessages(const std::string & params)
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
				result += (*it)->serialize();
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

std::string ServerInterface::getReceivedMessages(const std::string & params)
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
				result += (*it)->serialize();
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

std::string ServerInterface::sendMessage(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string recipient = param.at(1);
		std::string topic = param.at(2);
		std::string content = param.at(3);

		AbstractUser* user = Server::getInstance().data.getUser(param.at(0));
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

std::string ServerInterface::getCourseRequests(const std::string & params)
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
					result += (*it)->serialize();

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

std::string ServerInterface::getUserDepartmentCourses(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);

		AbstractUser* user = Server::getInstance().data.getUser(username);

		std::vector<Course*> courses = user->getDepartment()->getCourses();

		std::string result = "";
		if (!courses.empty())
		{
			for (std::vector<Course*>::iterator it = courses.begin(); it != courses.end(); ++it)
			{
				result += (*it)->serialize();

				if (courses.end() != it + 1)
				{
					result += ClientServerInterface::LIST_DELIMITER;
				}
			}
		}
		return result;

	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getUserDepartmentCourses" << e.what();
		return "";
	}
}

std::string ServerInterface::addCourse(const std::string & params)
{
	try {
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string courseCode = param.at(1);
		std::string courseName = param.at(2);
		std::string description = param.at(3);
		std::string credits = param.at(4);
		bool computer = Helper::stringToLong(param.at(5)) == 1;
		bool speaker = Helper::stringToLong(param.at(6)) == 1;
		bool accelerator = Helper::stringToLong(param.at(7)) == 1;

		AbstractUser* user = Server::getInstance().data.getUser(username);
		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::PROFESSOR)
			{
				Professor * prof = (Professor*)user;

				Constraint * constraint = new Constraint(computer, speaker, accelerator);
				bool success = prof->requestCourse(prof->getDepartmentId(), courseCode, courseName, description,
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

std::string ServerInterface::decideOnCourse(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string courseId = param.at(1);
		std::string status = param.at(2);

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

std::string ServerInterface::getDepartments(const std::string & params)
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
					result += (*it)->serialize();
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

std::string ServerInterface::givePrivileges(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string recipient = param.at(1);
		int departmentId = Helper::stringToLong(param.at(2));

		std::string result = "";
		AbstractUser* user = Server::getInstance().data.getUser(username);
		AbstractUser* recip = Server::getInstance().data.getUser(recipient);
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

std::string ServerInterface::getSections(const std::string & params)
{
	try
	{
		std::vector<Section*> sections;
		std::vector<Course*> courses = Server::getInstance().data.getCourses(Course::Status::APPROVED);
		for (std::vector<Course*>::iterator it = courses.begin();it != courses.end();++it)
		{
			sections.insert((*it)->getSections().end(), (*it)->getSections().begin(), (*it)->getSections().end());
		}


		std::string result = "";
		for (std::vector<Section*>::iterator it = sections.begin();it != sections.end();++it)
		{
			result += (*it)->serialize();

			if (sections.end() != it + 1)
			{
				result += ClientServerInterface::LIST_DELIMITER;
			}

			return result;
		}

		return "";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getSections" << e.what();
		return "";
	}
}

std::string ServerInterface::getUserSections(const std::string & params)
{
	try
	{
		AbstractUser* user = Server::getInstance().data.getUser(params);

		if (user != nullptr)
		{
			std::vector<Section*> sections;
			if (user->getType() == AbstractUser::Type::PROFESSOR)
			{
				Professor * prof = (Professor*)user;
				sections = prof->getSections();
			}
			else if (user->getType() == AbstractUser::Type::STUDENT)
			{
				Student * student = (Student*)user;
				sections = student->getSections();
			}
			std::string result = "";
			for (std::vector<Section*>::iterator it = sections.begin();it != sections.end();++it)
			{
				result += (*it)->serialize();

				if (sections.end() != it + 1)
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
		std::cerr << "Error in ServerInterface::getUserSections" << e.what();
		return "";
	}
}

std::string ServerInterface::resetPassword(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string recipient = param.at(1);

		std::string result = "";
		AbstractUser* user = Server::getInstance().data.getUser(username);
		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::ADMINISTRATOR)
			{
				Administrator * admin = (Administrator*)user;
				admin->resetUserPassword(recipient);
				return  "true";
			}
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::resetPassword" << e.what();
		return "false";
	}
}

std::string ServerInterface::changePassword(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		std::string oldPass = param.at(1);
		std::string newPass = param.at(2);

		std::string result = "";
		AbstractUser* user = Server::getInstance().data.getUser(username);
		if (user != nullptr)
		{
			bool success = user->setPassword(oldPass, newPass);
			return success ? "true" : "false";
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::changePassword" << e.what();
		return "false";
	}
}

std::string ServerInterface::publishSection(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		int courseId = Helper::stringToLong(param.at(1));
		int capacity = Helper::stringToLong(param.at(2));
		std::string timeslots = param.at(3);

		AbstractUser* user = Server::getInstance().data.getUser(username);

		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::PROFESSOR)
			{
				Professor * prof = (Professor*)user;
				std::vector<TimeSlot*> actualTimeslots;
				std::vector<std::string> slots = this->split(timeslots, ClientServerInterface::LIST_TIMESLOT_DELIMITER);
				for (std::vector<std::string>::iterator it = slots.begin();it != slots.end();++it)
				{
					std::vector<std::string> tslots = this->split((*it), ClientServerInterface::TIMESLOT_DELIMITER);
					TimeSlot * slot = new TimeSlot(static_cast<TimeSlot::Day>(Helper::stringToLong(tslots.at(0))), Helper::stringToLong(tslots.at(1)),
						Helper::stringToLong(tslots.at(2)), Helper::stringToLong(tslots.at(3)), Helper::stringToLong(tslots.at(4)));
					actualTimeslots.push_back(slot);
				}
				bool success = prof->publishSection(courseId, capacity, actualTimeslots);
				return success ? "true" : "false";
			}
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::addSection" << e.what();
		return "false";
	}
}

std::string ServerInterface::addSection(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		int crn = Helper::stringToLong(param.at(1));

		AbstractUser* user = Server::getInstance().data.getUser(username);

		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::STUDENT)
			{
				Student * student = (Student*)user;

				bool success = student->subscribeToSection(crn);
				return success ? "true" : "false";
			}
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::addSection" << e.what();
		return "false";
	}
}

std::string ServerInterface::editSection(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		int crn = Helper::stringToLong(param.at(1));
		int capacity = Helper::stringToLong(param.at(2));
		std::string timeslots = param.at(3);

		AbstractUser* user = Server::getInstance().data.getUser(username);

		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::PROFESSOR)
			{
				Professor * prof = (Professor*)user;

				std::vector<TimeSlot*> actualTimeslots;
				std::vector<std::string> slots = this->split(timeslots, ClientServerInterface::LIST_TIMESLOT_DELIMITER);
				for (std::vector<std::string>::iterator it = slots.begin();it != slots.end();++it)
				{
					std::vector<std::string> tslots = this->split((*it), ClientServerInterface::TIMESLOT_DELIMITER);
					TimeSlot * slot = new TimeSlot(static_cast<TimeSlot::Day>(Helper::stringToLong(tslots.at(0))), Helper::stringToLong(tslots.at(1)),
						Helper::stringToLong(tslots.at(2)), Helper::stringToLong(tslots.at(3)), Helper::stringToLong(tslots.at(4)));
					actualTimeslots.push_back(slot);
				}

				bool success = prof->editSection(crn, capacity, actualTimeslots);
				return success ? "true" : "false";
			}
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::deleteSection" << e.what();
		return "false";
	}
}

std::string ServerInterface::deleteSection(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		int crn = Helper::stringToLong(param.at(1));

		AbstractUser* user = Server::getInstance().data.getUser(username);

		if (user != nullptr)
		{
			if (user->getType() == AbstractUser::Type::PROFESSOR)
			{
				Professor * prof = (Professor*)user;
				bool success = prof->unpublishSection(crn);
				return success ? "true" : "false";
			}
			else if (user->getType() == AbstractUser::Type::STUDENT)
			{
				Student * student = (Student*)user;
				bool success = student->unsubscribeFromSection(crn);
				return success ? "true" : "false";
			}
		}
		return "false";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::deleteSection" << e.what();
		return "false";
	}
}

std::string ServerInterface::getUserDepartmentSections(const std::string & params)
{
	try
	{
		AbstractUser* user = Server::getInstance().data.getUser(params);

		if (user != nullptr)
		{
			std::vector<Section*> sections;
			std::vector<Course*> courses;
			courses = user->getDepartment()->getCourses();

			std::string result = "";
			for (std::vector<Course*>::iterator it = courses.begin();it != courses.end();++it)
			{
				sections = (*it)->getSections();
				for (std::vector<Section*>::iterator it = sections.begin();it != sections.end();++it)
				{
					result += (*it)->serialize();

					if (sections.end() != it + 1)
					{
						result += ClientServerInterface::LIST_DELIMITER;
					}
				}
			}

			return result;
		}

		return "";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getUserSections" << e.what();
		return "";
	}
}


std::string ServerInterface::getCourseSections(const std::string & params)
{
	try
	{
		std::vector<std::string> param = this->split(params, ClientServerInterface::DELIMITER);

		std::string username = param.at(0);
		int courseId = Helper::stringToLong(param.at(1));

		Course* course = Server::getInstance().data.getCourse(courseId);

		std::vector<Section*> sections;
		sections = course->getSections();

		std::string result = "";
		for (std::vector<Section*>::iterator it = sections.begin();it != sections.end();++it)
		{
			result += (*it)->serialize();

			if (sections.end() != it + 1)
			{
				result += ClientServerInterface::LIST_DELIMITER;
			}

			return result;
		}

		return "";
	}
	catch (std::exception& e)
	{
		std::cerr << "Error in ServerInterface::getCourseSections" << e.what();
		return "";
	}
}
