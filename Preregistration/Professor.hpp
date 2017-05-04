#pragma once

#include "AbstractUser.hpp"
#include "Schedulable.h"
#include "Schedule.h"
#include "Course.hpp"
#include "Section.hpp"
#include <vector>

class Professor : public AbstractUser, public Schedulable {
public:
	Professor();
	Professor(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, int departmentId, const std::string & birthday);
	Professor(int id, const std::string & username, const std::string & password, const std::string & firstName,
		const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm,
		int departmentId, const std::string & birthday);
	Professor(const Professor & other);
	virtual ~Professor();
	Professor & operator=(const Professor & rhs);

	const std::vector<Section *> getSections() const override;

	bool requestCourse(Course * course) const;

	bool publishSection(Section * section);

private:
	std::vector<Section *> m_sections;
};