#include "Department.hpp"

Department::Department()
{
}

Department::Department(const std::string & name, const std::string & code, const std::string & facultyCode)
{
}

Department::Department(int id, const std::string & name, const std::string & code, const std::string & facultyCode)
{
}

Department::Department(const Department & other)
{
}

Department::~Department()
{
}

Department & Department::operator=(const Department & rhs)
{
	// TODO: insert return statement here
}

const std::list<Course*>& Department::getCourses() const
{
	// TODO: insert return statement here
}

const std::list<Course*>& Department::getCourseRequests() const
{
	// TODO: insert return statement here
}

bool Department::requestCourse(Course * course)
{
	return false;
}

bool Department::decideOnCourse(Course * course, bool approveCourse)
{
	return false;
}
