#include "Department.hpp"
#include "Server.hpp"
#include "AbstractUser.hpp"
#include <algorithm>

//TODO: course/course requests
Department::Department(const std::string & name, const std::string & code, const std::string & facultyCode) :
	m_name(name), m_code(code), m_facultyCode(facultyCode), m_courseIds(), m_courseRequestIds(), m_courses(),
	m_courseRequests()
{
	m_id = Server::getInstance().repository->createDepartment(this);
	Server::getInstance().data.addDepartment(this);
}

Department::Department(int id, const std::string & name, const std::string & code, const std::string & facultyCode) :
	m_id(id), m_name(name), m_code(code), m_facultyCode(facultyCode),
	m_courseIds(Server::getInstance().repository->getDepartmentCourses(id)),
	m_courseRequestIds(Server::getInstance().repository->getDepartmentCourseRequests(id))
{
}

Department::Department(const Department & other) :
	m_id(other.m_id), m_name(other.m_name), m_code(other.m_code), m_facultyCode(other.m_facultyCode),
	m_courses(other.m_courses), m_courseRequests(other.m_courseRequests)
{
}

Department::~Department()
{
}

Department & Department::operator=(const Department & rhs)
{
	m_id = rhs.m_id;
	m_name = rhs.m_name;
	m_code = rhs.m_code;
	m_facultyCode = rhs.m_code;
	m_courses = rhs.m_courses;
	m_courseRequests = rhs.m_courseRequests;
	return *this;
}

int Department::getId() const
{
	return m_id;
}

void Department::setName(const std::string & name)
{
	m_name = name;
}

std::string Department::getName() const
{
	return m_name;
}

void Department::setCode(const std::string & code)
{
	m_code = code;
}

std::string Department::getCode() const
{
	return m_code;
}

void Department::setFacultyCode(const std::string & facultyCode)
{
	m_facultyCode = facultyCode;
}

std::string Department::getFacultyCode() const
{
	return m_facultyCode;
}

const std::vector<Course*>& Department::getCourses() const
{
	return m_courses;
}

const std::vector<Course*>& Department::getCourseRequests() const
{
	return m_courseRequests;
}

bool Department::requestCourse(Course * course)
{
	getCourseRequests();
	m_courseRequestIds.push_back(course->getID());
	m_courseRequests.push_back(course);
	return true;
}

// TODO update database
bool Department::decideOnCourse(Course * course, bool approveCourse)
{
	std::vector<Course*>::iterator it = std::find(m_courseRequests.begin(), m_courseRequests.end(), course);
	if (it == m_courseRequests.end()) {
		std::cerr << "Department::decideOnCourse: course " << course->getID() << " is not a request" << std::endl;
		return false;
	}
	else {
		Course * course = *it;
		if (approveCourse) {
			course->approveCourse();
		}
		else {
			course->refuseCourse();
		}
		m_courses.push_back(course);
		m_courseRequests.erase(it);
		return true;
	}
}

std::vector<AbstractUser*> Department::getUsers() const
{
	return Server::getInstance().data.getDepartmentUsers(this);
}

Department::Department() : m_id(), m_name(), m_code(), m_facultyCode(), m_courses(), m_courseRequests()
{
}