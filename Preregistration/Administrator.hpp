#pragma once

#include "AbstractUser.hpp"
#include <list>

class Administrator : public AbstractUser {
public:
	Administrator();
	Administrator(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, Department * department, const std::string & birthday);
	Administrator(int id, const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, Department * department, const std::string & birthday);
	Administrator(const Administrator & other);
	virtual ~Administrator();
	Administrator & operator=(const Administrator & rhs);

	AbstractUser * createUser(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int enrollmentYear, int enrollmentTerm, Term::Term userType, Department * department,
		const std::string & birthday) const;

	bool decideOnCourse(Course *courseRequested, bool acceptCourse) const;

	const std::list<Department *> & getPrivileges() const;
	bool hasPrivilegeTo(Department *) const;
	bool givePrivilege(Administrator *administrator, Department * department) const;

private:
	std::list<Department *> m_privileges; ///< List of departments the Administrator has privileges in

};