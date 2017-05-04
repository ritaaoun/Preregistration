#pragma once

#include "Course.hpp"
#include <string>
#include <vector>

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

	const std::vector<Course *> & getCourses() const;
	const std::vector<Course *> & getCourseRequests() const;
	bool requestCourse(Course *course);
	bool decideOnCourse(Course *course, bool approveCourse);

protected:
	Department();

private:
	int m_id;
	std::string m_name;
	std::string m_code;
	std::string m_facultyCode; ///< Faculty department belongs to

	std::vector<int> m_courseIds;
	std::vector<int> m_courseRequestIds;

	std::vector<Course *> m_courses;
	std::vector<Course *> m_courseRequests;
};