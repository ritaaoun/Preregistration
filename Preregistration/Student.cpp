#include "Student.hpp"

Student::Student() :
	AbstractUser(), m_sections()
{
}

Student::Student(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, int departmentId, const std::string & birthday) :
	AbstractUser(firstName, middleName, lastName, startYear, startTerm, Type::STUDENT, departmentId, birthday),
	m_sections()
{
}

//TODO: Get sections from db
Student::Student(int id, const std::string & username, const std::string & password, const std::string & firstName,
	const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm, 
	int departmentId, const std::string & birthday) :
	AbstractUser(id, username, password, firstName, middleName, lastName, startYear, startTerm,
		Type::STUDENT, departmentId, birthday),
	m_sections()
{
}

Student::Student(const Student & other) :
	AbstractUser(other), m_sections(other.m_sections)
{
}

Student::~Student()
{
}

Student & Student::operator=(const Student & rhs)
{
	AbstractUser::operator=(rhs);
	m_sections = rhs.m_sections;
	return *this;
}

const std::list<Section*>& Student::getSections() const
{
	return m_sections;
}

bool Student::subscribeToSection(Section * section)
{
	m_sections.push_back(section);
	return true;
}
