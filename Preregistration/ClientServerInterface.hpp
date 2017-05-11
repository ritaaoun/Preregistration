#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

class ClientServerInterface
{
public:
	virtual std::string login(const std::string & params) = 0;
	virtual std::string getUsers(const std::string & params) = 0;
	virtual  std::string addUser(const std::string & params) = 0;
	virtual  std::string editUser(const std::string & params) = 0;
	virtual  std::string resetPassword(const std::string & params) = 0;
	virtual  std::string changePassword(const std::string & params) = 0;

	virtual  std::string getSentMessages(const std::string & params) = 0;
	virtual  std::string getReceivedMessages(const std::string & params) = 0;
	virtual  std::string sendMessage(const std::string & params) = 0;

	virtual  std::string getCourseRequests(const std::string & params) = 0;
	virtual  std::string getUserDepartmentCourses(const std::string & params) = 0;
	virtual  std::string addCourse(const std::string & params) = 0;
	virtual  std::string decideOnCourse(const std::string & params) = 0;

	virtual  std::string getDepartments(const std::string & params) = 0;

	virtual  std::string givePrivileges(const std::string & params) = 0;

	virtual  std::string getSections(const std::string & params) = 0;
	virtual  std::string getUserSections(const std::string & params) = 0;
	virtual  std::string addSection(const std::string & params) = 0;
	virtual  std::string editSection(const std::string & params) = 0;
	virtual  std::string deleteSection(const std::string & params) = 0;
	virtual  std::string getUserDepartmentSections(const std::string & params) = 0;


	static std::vector<std::string> split(const std::string & s, std::string delim);
	static const std::string DELIMITER;
	static const std::string FUNC_DELIMITER;
	static const std::string TIMESLOT_DELIMITER;
	static const std::string LIST_DELIMITER;
	static const std::string LIST_TIMESLOT_DELIMITER;
};


