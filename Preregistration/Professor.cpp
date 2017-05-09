#include "Professor.hpp"
#include "Server.hpp"

Professor::Professor() : AbstractUser(), m_sections()
{
}

Professor::Professor(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, int departmentId, const std::string & birthday) :
	AbstractUser(firstName, middleName, lastName, startYear, startTerm, Type::PROFESSOR, departmentId, birthday),
	m_sectionIds(), m_sections()
{
}

Professor::Professor(int id, const std::string & username, const std::string & password, const std::string & firstName,
	const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm,
	int departmentId, const std::string & birthday) :
	AbstractUser(id, username, password, firstName, middleName, lastName, startYear, startTerm, Type::PROFESSOR,
		departmentId, birthday),
	m_sectionIds(Server::getInstance().repository->getUserSections(id)), m_sections()
{
}

Professor::Professor(const Professor & other) :
	AbstractUser(other), m_sectionIds(other.m_sectionIds), m_sections(other.m_sections)
{
}

Professor::~Professor()
{
}

Professor & Professor::operator=(const Professor & rhs)
{
	AbstractUser::operator=(rhs);
	m_sectionIds = rhs.m_sectionIds;
	m_sections = rhs.m_sections;
	return *this;
}

const std::vector<Section*> Professor::getSections()
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

bool Professor::requestCourse(int departmentId, const std::string & courseCode, const std::string & courseName, const std::string & courseDescription, int numberOfCredits, Constraint * constraints) const
{
	Course * course = new Course(departmentId, courseCode, courseName, courseDescription, numberOfCredits, constraints);
	return course->getDepartment()->requestCourse(course);
}

//TODO Create section inside
bool Professor::publishSection(Section * section)
{
	m_sections.push_back(section);
	return true;
}
