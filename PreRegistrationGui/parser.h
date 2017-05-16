#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <user.h>
#include <unordered_map>
#include <vector>
#include <ClientInterface.hpp>
#include "userinfo.h"
#include "message.h"
#include "course.h"

class Parser
{
public:
    Parser();

    static std::vector<std::string> getStdVector(std::vector<QString> qStringVector);

    static std::string sendActiveUser();
    static std::string sendCredentials(std::string username, std::string password);
    static std::string sendCreateUserInfo(std::string admin, std::vector<std::string> userInfo);
    static std::string sendMessage(Message message);
    static std::string sendPrivilges(std::string username, std::string adminUsername, std::string department);
    static std::string sendDecideOnCourse(std::string username, int id, bool accepted);
    static std::string sendChangePassword(std::string username, std::string oldPassowrd, std::string newPassword);
    static std::string sendResetPassword(std::string username, std::string userUsername);
    static std::string sendPusblishSection(std::string username, int courseId, int capacity, std::vector<TimeSlot> timeSlots);
    static std::string sendEditSection(std::string username, int crn, int capacity, std::vector<TimeSlot> timeSlots);
    static std::string sendRequestCourse(std::string username, std::string courseName, std::string courseNumber, std::string courseDescription,
                                         int numberOfCreadits, bool needsComputers, bool needsSpeakers, bool needsHighEnergyParticleAccelerator);
    static std::string sendRemoveSection(std::string username, int crn);
    static std::string sendAddSection(std::string username, int crn);
    static std::string sendConfirmSection(std::string username, int crn);

    static void getCreateUser(std::string message);
    static bool getBoolean(std::string message);
    static std::unordered_map<int, QString>  getDepartments(std::string message);
    static std::vector<UserInfo> getAdminUserInfo(std::string message);
    static std::vector<Message> getUserMessages(std::string message);
    static std::vector<Course> getCourseRequests(std::string message);
    static std::vector<Course> getSections(std::string message);
    static std::vector<Course> getDepartmentCourses(std::string message);
};

#endif // PARSER_H
