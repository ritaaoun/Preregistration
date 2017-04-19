#include "Administrator.hpp"
#include "SqliteRepository.hpp"
#include <algorithm>
#include "Professor.hpp"
#include "Student.hpp"

Administrator::Administrator() : AbstractUser(), m_privileges()
{
}

Administrator::Administrator(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, Department * department, const std::string & birthday) :
	AbstractUser(firstName, middleName, lastName, startYear, startTerm, Type::ADMINISTRATOR, department, birthday),
	m_privileges()
{
}

Administrator::Administrator(int id, const std::string & username, const std::string & password,
	const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, Department * department, const std::string & birthday,
	const std::list<Department *> & privileges) :
	AbstractUser(id, username, password, firstName, middleName, lastName, startYear, startTerm,
		Type::ADMINISTRATOR, department, birthday),
	m_privileges(privileges)
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
	const std::string & lastName, int startYear, Term::Term startTerm, Type userType, Department * department,
	const std::string & birthday) const
{
	AbstractUser * user;
	if (userType == Type::ADMINISTRATOR) {
		user = new Administrator(firstName, middleName, lastName, startYear, startTerm, department, birthday);
	}
	else if (userType == Type::PROFESSOR) {
		user = new Professor(firstName, middleName, lastName, startYear, startTerm, department, birthday);
	}
	else if (userType == Type::STUDENT) {
		user = new Student(firstName, middleName, lastName, startYear, startTerm, department, birthday);
	}
	else {
		return nullptr;
	}
	SqliteRepository::getInstance().createUser(user);
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

const std::list<Department*>& Administrator::getPrivileges() const
{
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
		SqliteRepository::getInstance().createPrivilege(administrator, department);
		return true;
	}
	else {
		return false;
	}
}
