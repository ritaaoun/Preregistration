#pragma once

#include "AbstractUser.hpp"
#include "Course.hpp"
#include <vector>
//TODO: editUser
class Administrator : public AbstractUser {
public:
	Administrator();
	Administrator(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, int departmentId, const std::string & birthday);
	Administrator(int id, const std::string & username, const std::string & password, const std::string & firstName,
		const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm,
		int departmentId, const std::string & birthday);
	Administrator(const Administrator & other);
	virtual ~Administrator();
	Administrator & operator=(const Administrator & rhs);

	AbstractUser * createUser(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, Type userType, int departmentId, const std::string & birthday) const;

	bool decideOnCourse(Course *courseRequested, bool approveCourse) const;

	const std::vector<Department *> getPrivileges();
	bool hasPrivilegeTo(Department * department) const;
	bool givePrivilege(Administrator *administrator, Department * department) const;

	std::vector<AbstractUser*> getUsers();

	bool editUser(std::string username, const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int departmentId, const std::string & birthday);

private:
	std::vector<int> m_privilegeIds;
	std::vector<Department *> m_privileges; ///< vector of departments the Administrator has privileges in

	std::vector<AbstractUser *> m_users;
};