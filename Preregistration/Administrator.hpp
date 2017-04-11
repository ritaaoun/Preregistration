#pragma once

#include "AbstractUser.hpp"
#include <vector>

class Administrator : public AbstractUser {
public:
	Administrator();
	Administrator(const std::string & firstName, const std::string & middleName, const std::string & lastName,
		int enrollmentYear, int enrollmentTerm, Term::Term userType, Department * department,
		const std::string & birthday);
	Administrator(Administrator & other);
	virtual ~Administrator();
	Administrator & operator=(Administrator & rhs);



private:


};