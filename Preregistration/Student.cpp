#include "Student.hpp"
#include "Server.hpp"

Student::Student() :
	AbstractUser(), m_sections()
{
}

Student::Student(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, int departmentId, const std::string & birthday) :
	AbstractUser(firstName, middleName, lastName, startYear, startTerm, Type::STUDENT, departmentId, birthday),
	m_sectionIds(), m_sections()
{
}

Student::Student(int id, const std::string & username, const std::string & password, const std::string & firstName,
	const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm, 
	int departmentId, const std::string & birthday) :
	AbstractUser(id, username, password, firstName, middleName, lastName, startYear, startTerm,
		Type::STUDENT, departmentId, birthday),
	m_sectionIds(Server::getInstance().repository->getUserSections(id)), m_sections()
{
}

Student::Student(const Student & other) :
	AbstractUser(other), m_sectionIds(other.m_sectionIds), m_sections(other.m_sections)
{
}

Student::~Student()
{
}

Student & Student::operator=(const Student & rhs)
{
	AbstractUser::operator=(rhs);
	m_sections = rhs.m_sections;
	m_sectionIds = rhs.m_sectionIds;
	return *this;
}

const std::vector<Section*> Student::getSections()
{
	if (m_sections.empty())
	{
		for (std::vector<int>::iterator it = m_sectionIds.begin(); it != m_sectionIds.end(); ++it)
		{
			m_sections.push_back(Server::getInstance().data.getSection(*it));
		}

	}
	return m_sections;
}

bool Student::subscribeToSection(Section * section)
{
	m_sections.push_back(section);
	return true;
}
