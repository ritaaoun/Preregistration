#pragma once

#include "AbstractUser.hpp"
#include "Course.hpp"
#include <list>

class Administrator : public AbstractUser {
public:
	Administrator();
	Administrator(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, int departmentId, const std::string & birthday);
	Administrator(int id, const std::string & username, const std::string & password, const std::string & firstName,
		const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm,
		int departmentId, const std::string & birthday, const std::list<Department *> & privileges);
	Administrator(const Administrator & other);
	virtual ~Administrator();
	Administrator & operator=(const Administrator & rhs);

	AbstractUser * createUser(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, Type userType, int departmentId, const std::string & birthday) const;

	bool decideOnCourse(Course *courseRequested, bool approveCourse) const;

	const std::list<Department *> & getPrivileges() const;
	bool hasPrivilegeTo(Department * department) const;
	bool givePrivilege(Administrator *administrator, Department * department) const;

private:
	std::list<Department *> m_privileges; ///< List of departments the Administrator has privileges in

};