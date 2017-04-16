#pragma once

#include "Course.hpp"
#include <string>
#include <list>

class Department {
public:
	Department();
	Department(const std::string & name, const std::string & code, const std::string & facultyCode);
	Department(int id, const std::string & name, const std::string & code, const std::string & facultyCode);
	Department(const Department & other);
	virtual ~Department();
	Department & operator=(const Department & rhs);

private:
	int m_id;
	std::string m_name;
	std::string m_code;
	std::string m_facultyCode; ///< Faculty department belongs to
	std::list<Course *> m_courses;
};