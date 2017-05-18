#ifndef APISERVICE_H
#define APISERVICE_H
#include <vector>
#include <unordered_map>
#include <course.h>
#include <user.h>
#include <courserequest.h>
#include <parser.h>
#include <ClientInterface.hpp>
#include <QDebug>
#include "userinfo.h"
#include "message.h"

class APIService
{
public:
    static APIService* getInstance();

    std::vector<Course> getCourseRequests();
    std::unordered_map<int, QString> getDepartments();
    std::vector<UserInfo> getAdminUsersInfo();
    std::vector<Message> getUserSentMessages();
    std::vector<Message> getUserReceivedMessages();
    std::vector<Course> getUserSections();
    std::vector<Course> getUserDepartmentCourses();
    std::vector<Course> getDepartmentSections();
    bool userLogIn(QString username, QString password);
    bool createUser(std::vector<QString> userInfo);
    bool editUser(std::vector<QString> userInfo);
    bool sendPrivileges(QString adminUsername, int adminDepartment);
    bool sendMessage(Message message);
    bool decideOnCourse(Course course, bool accepted);
    bool changePassword(QString oldPassword, QString newPassword);
    bool resetPassword(QString userUsername);
    bool publishSection(int courseId, int capacity, std::vector<TimeSlot> timeSlots);
    bool editSection(int crn, int capacity, std::vector<TimeSlot> timeSlots);
    bool removeSection(int crn);
    bool addSection(int crn);
    bool confirmSection(int crn);
    bool requestCourse(QString courseName, QString courseNumber, QString courseDescription, int numberOfCreadits,
                       bool needsComputers, bool needsSpeakers, bool needsHighEnergyParticleAccelerator);

private:
    APIService();
    static APIService* service;
    ClientInterface client;
};

#endif // APISERVICE_H
