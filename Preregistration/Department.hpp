#pragma once

#include "Course.hpp"
#include <string>
#include <vector>
#include "ISerializable.hpp"

class AbstractUser;

class Department : public ISerializable {
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

	const std::vector<Course *> & getCourses();
	const std::vector<Course *> & getCourseRequests();
	bool requestCourse(Course *course);
	bool decideOnCourse(Course *course, bool approveCourse);

	std::vector<AbstractUser*> getUsers() const;

	// Inherited via ISerializable
	virtual std::string serialize() override;

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

	void loadCourses();
	void loadCourseRequests();

};