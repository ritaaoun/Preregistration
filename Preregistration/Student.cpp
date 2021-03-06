#include "Student.hpp"
#include "Server.hpp"
#include <iostream>

Student::Student() :
	AbstractUser(), m_sectionCrns(), m_sections()
{
}

Student::Student(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, int departmentId, const std::string & birthday) :
	AbstractUser(firstName, middleName, lastName, startYear, startTerm, Type::STUDENT, departmentId, birthday),
	m_sectionCrns(), m_sections()
{
}

Student::Student(int id, const std::string & username, const std::string & password, const std::string & firstName,
	const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm, 
	int departmentId, const std::string & birthday) :
	AbstractUser(id, username, password, firstName, middleName, lastName, startYear, startTerm,
		Type::STUDENT, departmentId, birthday),
	m_sectionCrns(Server::getInstance().repository->getUserSections(id)), m_sections()
{
}

Student::Student(const Student & other) :
	AbstractUser(other), m_sectionCrns(other.m_sectionCrns), m_sections(other.m_sections)
{
}

Student::~Student()
{
}

Student & Student::operator=(const Student & rhs)
{
	AbstractUser::operator=(rhs);
	m_sections = rhs.m_sections;
	m_sectionCrns = rhs.m_sectionCrns;
	return *this;
}

const std::vector<Section*> Student::getSections()
{
	loadSections();
	return m_sections;
}

bool Student::subscribeToSection(Section * section)
{
	loadSections();
	if (std::find(m_sections.begin(), m_sections.end(), section) == m_sections.end())
	{
		m_sectionCrns.push_back(section->getCrn());
		m_sections.push_back(section);
		section->addStudent(this);
		Server::getInstance().repository->addStudentSection(this, section);
		return true;
	}
	else
	{
		std::cout << "Student::subscribeToSection: Student " << getId() << " is already subscribed to section " << section->getCrn() << std::endl;
		return false;
	}
}

bool Student::subscribeToSection(int sectionCrn)
{
	return subscribeToSection(Server::getInstance().data.getSection(sectionCrn));
}

bool Student::unsubscribeFromSection(Section * section)
{
	if (std::find(m_sections.begin(), m_sections.end(), section) != m_sections.end()) {
		loadSections();
		m_sectionCrns.erase(std::find(m_sectionCrns.begin(), m_sectionCrns.end(), section->getCrn()));
		m_sections.erase(std::find(m_sections.begin(), m_sections.end(), section));
		section->removeStudent(this);
		Server::getInstance().repository->removeStudentSection(this, section);
		return true;
	}
	return false;
}

bool Student::unsubscribeFromSection(int sectionCrn)
{
	return unsubscribeFromSection(Server::getInstance().data.getSection(sectionCrn));
}

void Student::loadSections()
{
	if (m_sections.empty())
	{
		for (std::vector<int>::iterator it = m_sectionCrns.begin(); it != m_sectionCrns.end(); ++it)
		{
			m_sections.push_back(Server::getInstance().data.getSection(*it));
		}
	}
}
