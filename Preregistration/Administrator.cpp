#include "Administrator.hpp"
#include "Server.hpp"
#include <algorithm>
#include "Professor.hpp"
#include "Student.hpp"
#include <iostream>

Administrator::Administrator() : AbstractUser(), m_privilegeIds(), m_privileges()
{
}

Administrator::Administrator(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, int departmentId, const std::string & birthday) :
	AbstractUser(firstName, middleName, lastName, startYear, startTerm, Type::ADMINISTRATOR, departmentId, birthday),
	m_privilegeIds(), m_privileges()
{
}

Administrator::Administrator(int id, const std::string & username, const std::string & password,
	const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, int departmentId, const std::string & birthday) :
	AbstractUser(id, username, password, firstName, middleName, lastName, startYear, startTerm,
		Type::ADMINISTRATOR, departmentId, birthday),
	m_privilegeIds(Server::getInstance().repository->getAdminPrivileges(id)), m_privileges()
{
}

Administrator::Administrator(const Administrator & other) :
	AbstractUser(other), m_privileges(other.m_privileges)
{
}

Administrator::~Administrator()
{
}

Administrator & Administrator::operator=(const Administrator & rhs)
{
	AbstractUser::operator=(rhs);
	m_privileges = rhs.m_privileges;
	return *this;
}

AbstractUser * Administrator::createUser(const std::string & firstName, const std::string & middleName,
	const std::string & lastName, int startYear, Term::Term startTerm, Type userType, int departmentId,
	const std::string & birthday) const
{
	Department * department = Server::getInstance().data.getDepartment(departmentId);
	if (hasPrivilegeTo(department)) {
		AbstractUser * user;
		if (userType == Type::ADMINISTRATOR) {
			user = new Administrator(firstName, middleName, lastName, startYear, startTerm, departmentId, birthday);
		}
		else if (userType == Type::PROFESSOR) {
			user = new Professor(firstName, middleName, lastName, startYear, startTerm, departmentId, birthday);
		}
		else if (userType == Type::STUDENT) {
			user = new Student(firstName, middleName, lastName, startYear, startTerm, departmentId, birthday);
		}
		else {
			std::cerr << "Administrator::createUser: undefined userType " + std::to_string(userType) << std::endl;
			return nullptr;
		}
		std::cout << "Administrator::createUser: user " + std::to_string(user->getId()) << " created" << std::endl;

		return user;
	}
	else {
		std::cout << "Administrator::createUser: admin " + std::to_string(getId()) + " does not have privilege to department " <<
			std::to_string(department->getId()) << std::endl;
		return nullptr;
	}
}

bool Administrator::decideOnCourse(Course * courseRequested, bool approveCourse) const
{
	Department * courseDepartment = courseRequested->getDepartment();
	if (hasPrivilegeTo(courseDepartment)) {
		courseDepartment->decideOnCourse(courseRequested, approveCourse);
		std::cout << "Administrator::decideOnCourse: course " << courseRequested->getID() << " was decided on" << std::endl;
		return true;
	}
	else {
		std::cerr << "Administrator::decideOnCourse: Administrator " << getId() << " does not have privileges over department " <<
			courseDepartment->getId() << std::endl;
		return false;
	}
}

const std::vector<Department*> Administrator::getPrivileges()
{
	if (m_privileges.empty() && !m_privilegeIds.empty())
	{
		loadPrivileges();
	}
	return m_privileges;
}

bool Administrator::hasPrivilegeTo(Department * department) const
{
	return std::find(m_privileges.begin(), m_privileges.end(), department) != m_privileges.end();
}

bool Administrator::givePrivilege(Administrator * administrator, Department * department) const
{
	if (std::find(m_privileges.begin(), m_privileges.end(), department) != m_privileges.end()) {
		administrator->m_privileges.push_back(department);
		Server::getInstance().repository->createPrivilege(administrator, department);
		return true;
	}
	else {
		return false;
	}
}

std::vector<AbstractUser*> Administrator::getUsers()
{
	std::vector<AbstractUser*> out;

	if (!m_privilegeIds.empty()) {
		if (m_privileges.empty()) {
			loadPrivileges();
		}

		for (std::vector<Department*>::const_iterator it = m_privileges.begin(); it != m_privileges.end(); ++it) {
			std::vector<AbstractUser*> departmentUsers = Server::getInstance().data.getDepartmentUsers(*it);

			for (std::vector<AbstractUser*>::const_iterator user = departmentUsers.begin(); user != departmentUsers.end(); ++user) {
				out.push_back(*user);
			}
		}
	}
	return out;
}

std::vector<Course*> Administrator::getCourseRequests()
{
	loadPrivileges();
	std::vector<Course *> out;
	for (std::vector<Department *>::const_iterator it = m_privileges.begin(); it != m_privileges.end(); ++it) {
		std::vector<Course *> requests = (*it)->getCourseRequests();
		for (std::vector<Course *>::const_iterator it2 = requests.begin(); it2 != requests.end(); ++it2) {
			out.push_back(*it2);
		}
	}
	return out;
}

bool Administrator::resetUserPassword(const std::string & username)
{
	AbstractUser * user = Server::getInstance().data.getUser(username);
	if (std::find(m_privilegeIds.begin(), m_privilegeIds.end(), user->getDepartmentId()) != m_privilegeIds.end()) {
		user->resetPassword();
		std::cout << "Administrator::resetUserPassword: password of " << user->getId() << " was reset" << std::endl;
		return true;
	}
	else {
		std::cerr << "Administrator::resetUserPassword: The administrator " << getId() << " does not have privilege over user " << getId() << std::endl;
		return false;
	}
}

void Administrator::loadPrivileges()
{
	for (std::vector<int>::iterator it = m_privilegeIds.begin(); it != m_privilegeIds.end(); ++it)
	{
		m_privileges.push_back(Server::getInstance().data.getDepartment(*it));
	}
}

bool Administrator::editUser(std::string username, const std::string & firstName, const std::string & middleName, const std::string & lastName, int departmentId, const std::string & birthday)
{
	AbstractUser * user = Server::getInstance().data.getUser(username);
	if (hasPrivilegeTo(user->getDepartment())) {
		user->setFirstName(firstName);
		user->setMiddleName(middleName);
		user->setLastName(lastName);
		user->setDepartmentId(departmentId);
		user->setBirthday(birthday);
		Server::getInstance().repository->updateUser(user);
		std::cout << "Administrator " << getId() << " successfully edited User " << user->getId() << std::endl;
		return true;
	}
	else {
		std::cout << "Administrator " << getId() << " has no privilege over User " << user->getId() << std::endl;
		return false;
	}
}
