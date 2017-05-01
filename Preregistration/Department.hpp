#pragma once

#include "Course.hpp"
#include <string>
#include <list>

class Department {
public:
	Department(const std::string & name, const std::string & code, const std::string & facultyCode);
	Department(int id, const std::string & name, const std::string & code, const std::string & facultyCode);
	Department(const Department & other);
	virtual ~Department();
	Department & operator=(const Department & rhs);

	int getId() const;

	void setName(const std::string & name);
	std::string getName() const;

	void setCode(const std::string & code);
	std::string getCode() const;

	void setFacultyCode(const std::string & facultyCode);
	std::string getFacultyCode() const;

	const std::list<Course *> & getCourses() const;
	const std::list<Course *> & getCourseRequests() const;
	bool requestCourse(Course *course);
	bool decideOnCourse(Course *course, bool approveCourse);

protected:
	Department();

private:
	int m_id;
	std::string m_name;
	std::string m_code;
	std::string m_facultyCode; ///< Faculty department belongs to
	std::list<Course *> m_courses;
	std::list<Course *> m_courseRequests;
};