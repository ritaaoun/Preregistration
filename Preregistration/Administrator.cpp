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
	m_privilegeIds(Server::getInstance().repository->getAdminDepartments(id)), m_privileges()
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
		return nullptr;
	}
	return user;
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
	if (m_privileges.empty())
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
