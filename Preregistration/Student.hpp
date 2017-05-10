#pragma once

#include "AbstractUser.hpp"
#include "Schedulable.h"
#include <vector>

class Student : public AbstractUser, public Schedulable {
public:
	Student();
	Student(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, int departmentId, const std::string & birthday);
	Student(int id, const std::string & username, const std::string & password, const std::string & firstName,
		const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm,
		int departmentId, const std::string & birthday);
	Student(const Student & other);
	virtual ~Student();
	Student & operator=(const Student & rhs);

	const std::vector<Section *> getSections() override;

	bool subscribeToSection(Section * section);
	bool unsubscribeFromSection(Section * section);

private:
	std::vector<int> m_sectionCrns;
	std::vector<Section *> m_sections;

	void loadSections();
};