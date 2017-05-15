#pragma once

#include "AbstractUser.hpp"
#include "ISchedulable.h"
#include <vector>

class Student : public AbstractUser, public ISchedulable {
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
	bool subscribeToSection(int sectionCrn);
	bool unsubscribeFromSection(Section * section);
	bool unsubscribeFromSection(int sectionCrn);

private:
	std::vector<int> m_sectionCrns;
	std::vector<Section *> m_sections;

	void loadSections();
};