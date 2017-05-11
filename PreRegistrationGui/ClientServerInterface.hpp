#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

class ClientServerInterface
{
public:
	virtual std::string login(std::string params) = 0;
	virtual std::string getUsers(std::string params) = 0;
    virtual std::string addUser(std::string params) = 0;
    virtual std::string editUser(std::string params) = 0;
    virtual std::string resetPassword(std::string params) = 0;
    virtual std::string changePassword(std::string params) = 0;

    virtual std::string getSentMessages(std::string params) = 0;
    virtual std::string getReceivedMessages(std::string params) = 0;
    virtual std::string sendMessage(std::string params) = 0;

    virtual std::string getCourseRequests(std::string params) = 0;
    virtual std::string getUserCourses(std::string params) = 0;
    virtual std::string addCourse(std::string params) = 0;
    virtual std::string decideOnCourse(std::string params) = 0;

    virtual std::string getDepartments(std::string params) = 0;

    virtual std::string givePrivileges(std::string params) = 0;

    virtual std::string getSections(std::string params) = 0;
    virtual std::string getUserSections(std::string params) = 0;
    virtual std::string getUserDepartmentSections(std::string params) = 0;

    virtual  std::string addSection(std::string params) = 0;
    virtual  std::string editSection(std::string params) = 0;



	static std::vector<std::string> split(const std::string & s, std::string delim);
	static const std::string DELIMITER;
	static const std::string FUNC_DELIMITER;
	static const std::string TIMESLOT_DELIMITER;
	static const std::string LIST_DELIMITER;
	static const std::string LIST_TIMESLOT_DELIMITER;
};


