#include "Administrator.hpp"
#include "Server.hpp"
#include <algorithm>
#include "Professor.hpp"
#include "Student.hpp"

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
	if (std::find(m_privileges.begin(), m_privileges.end(), courseDepartment) != m_privileges.end()) {
		courseDepartment->decideOnCourse(courseRequested, approveCourse);
		return true;
	}
	else {
		return false;
	}
}

const std::vector<Department*> Administrator::getPrivileges()
{
	if (m_privileges.empty() && !m_privilegeIds.empty())
	{
		for (std::vector<int>::iterator it = m_privilegeIds.begin(); it != m_privilegeIds.end(); ++it)
		{
			m_privileges.push_back(Server::getInstance().data.getDepartment(*it));
		}
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
			getPrivileges();
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
