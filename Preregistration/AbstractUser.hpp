#pragma once
#include <string>
#include "Enum.hpp"
#include "Department.hpp"
#include "Inbox.hpp"


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

	int getStartYear() const;
	void setStartYear(int year);

	Term::Term getStartTerm() const;
	void setStartTerm(Term::Term startTerm);

	Type getType() const;
	void setType(Type type);

	Department * getDepartment() const;
	void setDepartment(Department * department);

	std::string getBirthday() const;
	void setBirthday(const std::string & birthday);

	bool updateSentMessages(AbstractMessage * message);
	bool updateReceivedMessages(AbstractMessage * message);

protected:
	AbstractUser();
	AbstractUser(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int startYear, Term::Term startTerm, Type userType, Department * department,
		const std::string & birthday);
	AbstractUser(int id, const std::string & username, const std::string & password, const std::string & firstName,
		const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm,
		Type userType, Department * department, const std::string & birthday);
	AbstractUser(const AbstractUser & other);
	virtual ~AbstractUser();
	AbstractUser & operator=(const AbstractUser & rhs);
	
private:
	int m_id; ///< User id
	std::string m_username, m_password; ///< User credentials
	std::string m_firstName, m_middleName, m_lastName; ///< User name
	int m_startYear; ///< Enrollment date
	Term::Term m_startTerm; ///< Enrollment term
	Type m_type; ///< User type
	Department * m_department; ///< Department the user belongs to
	std::string m_birthday; ///< User birthday in the format DD-MM-YYYY
	
	Inbox m_inbox; ///< User inbox
};