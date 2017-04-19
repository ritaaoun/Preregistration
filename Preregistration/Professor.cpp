#include "Professor.hpp"

Professor::Professor() : AbstractUser(), m_sections()
{
}

Professor::Professor(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, Department * department, const std::string & birthday) :
	AbstractUser(firstName, middleName, lastName, startYear, startTerm, Type::PROFESSOR, department, birthday),
	m_sections()
{
}

//TODO: Take sections from db
Professor::Professor(int id, const std::string & username, const std::string & password, const std::string & firstName,
	const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm,
	Department * department, const std::string & birthday) :
	AbstractUser(id, username, password, firstName, middleName, lastName, startYear, startTerm, Type::PROFESSOR,
		department, birthday),
	m_sections()
{
}

Professor::Professor(const Professor & other) :
	AbstractUser(other), m_sections(other.m_sections)
{
}

Professor::~Professor()
{
}

Professor & Professor::operator=(const Professor & rhs)
{
	AbstractUser::operator=(rhs);
	m_sections = rhs.m_sections;
	return *this;
}

const std::list<Section*>& Professor::getSections() const
{
	return m_sections;
}

bool Professor::requestCourse(Course * course) const
{
	return course->getDepartment()->requestCourse(course);
}

//TODO Create section inside
bool Professor::publishSection(Section * section)
{
	m_sections.push_back(section);
	return true;
}
