#pragma once

#include "AbstractUser.hpp"
#include "ISchedulable.h"
#include "Schedule.h"
#include "Course.hpp"
#include "Section.hpp"
#include <vector>

class Professor : public AbstractUser, public ISchedulable {
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

	const std::vector<Section *> getSections() override;

	bool requestCourse(int departmentId, const std::string & courseCode, const std::string & courseName, 
		const std::string & courseDescription, int numberOfCredits, Constraint * constraints) const;

	bool publishSection(int courseId, int capacity, const std::vector<TimeSlot*>& timeSlots);
	bool unpublishSection(Section * section);
	bool unpublishSection(int sectionCrn);

	bool editSectionCapacity(int sectionCrn, int capacity);
	bool editSectionTimeSlots(int sectionCrn, const std::vector<TimeSlot*>& timeSlots);
	bool editSection(int sectionCrn, int capacity, const std::vector<TimeSlot*>& timeSlots);

	bool confirmSection(int sectionCrn);

private:
	std::vector<int> m_sectionCrns;
	std::vector<Section *> m_sections;

	void loadSections();

	bool notifySectionStudents(Section * section, const std::string & topic, const std::string & message);
};