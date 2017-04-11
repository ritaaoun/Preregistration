#pragma once
#include <string>
#include "Enum.hpp"
#include "Department.hpp"

/**
* \file User.hpp
* \brief User class
*
* This is an abstract class. It provides functions to access and edit User information.
*/

class AbstractUser {
public:
	enum Type {Student, Professor, Administrator, TYPE_END};

	int getId() const;
	std::string getUsername() const;

	bool checkPassword(const std::string & password) const;
	void setPassword(const std::string & password);
	
	std::string getFirstName() const;
	void setFirstName(const std::string & firstName);

	std::string getMiddleName() const;
	void setMiddleName(const std::string & middleName);

	std::string getLastName() const;
	void setLastName(const std::string & lastName);

	int getEnrollmentYear() const;
	void setEnrollmentYear(int year);

	Term::Term getEnrollmentTerm() const;
	void setEnrollmentTerm(Term::Term enrollmentTerm);

	Department * getDepartment() const;
	void setDepartment(Department * department);

	std::string getBirthday() const;
	void setBirthday(const std::string & birthday);

protected:
	AbstractUser();
	AbstractUser(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int enrollmentYear, int enrollmentTerm, Term::Term userType, Department * department,
		const std::string & birthday);
	AbstractUser(AbstractUser & other);
	virtual ~AbstractUser();
	AbstractUser & operator=(const AbstractUser & rhs);
	
private:
	int m_id; ///< User id
	std::string m_username, m_password; ///< User credentials
	std::string m_firstName, m_middleName, m_lastName; ///< User name
	int m_enrollmentYear; ///< Enrollment date
	Term::Term m_enrollmentTerm; ///< Enrollment term
	Type m_type; ///< User type
	Department * m_department; ///< Department the user belongs to
	std::string m_birthday; ///< User birthday in the format DD-MM-YYYY
};