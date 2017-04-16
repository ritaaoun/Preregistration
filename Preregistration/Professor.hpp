#pragma once

#include "AbstractUser.hpp"
#include "Schedulable.hpp"
#include "Schedule.hpp"
#include "Course.hpp"
#include "Section.hpp"
#include <list>

class Professor : public AbstractUser, public Schedulable {
public:
	Professor();
	Professor(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, Department * department, const std::string & birthday);
	Professor(int id, const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, Department * department, const std::string & birthday);
	Professor(const Professor & other);
	virtual ~Professor();
	Professor & operator=(const Professor & rhs);

	const std::list<Section *> & getSections() const;

	const Schedule & getSchedule() const;

	bool requestCourse(Course * course) const;

	bool publishSection(Section * section);

private:
	std::list<Section *> m_sections;
	Schedule m_schedule;
};