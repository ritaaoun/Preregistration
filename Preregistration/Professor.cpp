#include "Professor.hpp"
#include "Server.hpp"
#include "Student.hpp"
#include <iostream>


Professor::Professor() : AbstractUser(), m_sections()
{
}

Professor::Professor(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, int departmentId, const std::string & birthday) :
	AbstractUser(firstName, middleName, lastName, startYear, startTerm, Type::PROFESSOR, departmentId, birthday),
	m_sectionCrns(), m_sections()
{
}

Professor::Professor(int id, const std::string & username, const std::string & password, const std::string & firstName,
	const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm,
	int departmentId, const std::string & birthday) :
	AbstractUser(id, username, password, firstName, middleName, lastName, startYear, startTerm, Type::PROFESSOR,
		departmentId, birthday),
	m_sectionCrns(Server::getInstance().repository->getUserSections(id)), m_sections()
{
}

Professor::Professor(const Professor & other) :
	AbstractUser(other), m_sectionCrns(other.m_sectionCrns), m_sections(other.m_sections)
{
}

Professor::~Professor()
{
}

Professor & Professor::operator=(const Professor & rhs)
{
	AbstractUser::operator=(rhs);
	m_sectionCrns = rhs.m_sectionCrns;
	m_sections = rhs.m_sections;
	return *this;
}

const std::vector<Section*> Professor::getSections()
{
	loadSections();
	return m_sections;
}

bool Professor::requestCourse(int departmentId, const std::string & courseCode, const std::string & courseName, 
	const std::string & courseDescription, int numberOfCredits, Constraint * constraints) const
{
	std::vector<Course *> coursesInDepartment = Server::getInstance().data.getDepartment(departmentId)->getCourses();
	for (std::vector<Course *>::const_iterator it = coursesInDepartment.begin(); it != coursesInDepartment.end(); ++it) {
		if ((*it)->getCode() == courseCode) {
			return false;
		}
	}

	std::vector<Course *> courseRequestsInDepartment = Server::getInstance().data.getDepartment(departmentId)->getCourseRequests();
	for (std::vector<Course *>::const_iterator it = courseRequestsInDepartment.begin(); it != courseRequestsInDepartment.end(); ++it) {
		if ((*it)->getCode() == courseCode) {
			return false;
		}
	}

	Course * course = new Course(departmentId, courseCode, courseName, courseDescription, numberOfCredits, constraints, getId());
	return course->getDepartment()->requestCourse(course);
}

bool Professor::publishSection(int courseId, int capacity, int professorId, const std::vector<TimeSlot*>& timeSlots)
{
	loadSections();
	Section * section = new Section(courseId, capacity, professorId, timeSlots);
	m_sectionCrns.push_back(section->getCrn());
	m_sections.push_back(section);

	section->getCourse()->addSection(section);
	return true;
}

bool Professor::unpublishSection(Section * section)
{
	loadSections();
	m_sectionCrns.erase(std::remove(m_sectionCrns.begin(), m_sectionCrns.end(), section->getCrn()), m_sectionCrns.end());
	m_sections.erase(std::remove(m_sections.begin(), m_sections.end(), section), m_sections.end());
	Server::getInstance().repository->removeProfessorSection(this, section);
	Server::getInstance().data.deleteSection(section);
	return true;
}

bool Professor::editSectionCapacity(int sectionCrn, int capacity)
{
	if (std::find(m_sectionCrns.begin(), m_sectionCrns.end(), sectionCrn) != m_sectionCrns.end()) {
		Section * section = Server::getInstance().data.getSection(sectionCrn);
		section->setCapacity(capacity);
		Server::getInstance().repository->updateSection(section);
		notifySectionStudents(section, "Capacity change", "The capacity of section " + std::to_string(section->getNumber()) +
			" of " + section->getCourse()->getFullCode() + " has changed");
		return true;
	}
	else {
		std::cerr << "Professor::editSectionCapacity: professor " << getId() << " does not own section " << sectionCrn;
		return false;
	}
}

bool Professor::editSectionTimeSlots(int sectionCrn, const std::vector<TimeSlot*>& timeSlots)
{
	if (std::find(m_sectionCrns.begin(), m_sectionCrns.end(), sectionCrn) != m_sectionCrns.end()) {
		Section * section = Server::getInstance().data.getSection(sectionCrn);
		section->setTimeSlots(timeSlots);
		Server::getInstance().repository->updateSectionTimeSlots(section);
		notifySectionStudents(section, "Time slot change", "The timing of section " + std::to_string(section->getNumber()) + 
			" of " + section->getCourse()->getFullCode() + " has changed");
		return true;
	}
	else {
		std::cerr << "Professor::editSectionCapacity: professor " << getId() << " does not own section " << sectionCrn;
		return false;
	}
}

bool Professor::editSection(int sectionCrn, int capacity, const std::vector<TimeSlot*>& timeSlots)
{
	return editSectionCapacity(sectionCrn, capacity) && editSectionTimeSlots(sectionCrn, timeSlots);
}

void Professor::loadSections()
{
	if (m_sections.empty() && !m_sectionCrns.empty())
	{
		for (std::vector<int>::iterator it = m_sectionCrns.begin(); it != m_sectionCrns.end(); ++it)
		{
			m_sections.push_back(Server::getInstance().data.getSection(*it));
		}

	}
}

bool Professor::notifySectionStudents(Section * section, const std::string & topic, const std::string & message)
{
	std::vector<Student *> students = section->getStudents();
	for (std::vector<Student *>::const_iterator it = students.begin(); it != students.end(); ++it) {
		sendChatMessage((*it)->getUsername(), topic, message);
	}
	return false;
}
