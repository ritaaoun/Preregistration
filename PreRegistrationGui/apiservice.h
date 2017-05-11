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

    std::vector<Course> getCoursesList();
    std::vector<Course> getUserCourses();
    std::vector<Course> getCourseRequests();
    std::unordered_map<int, QString> getDepartments();
    std::vector<UserInfo> getAdminUsersInfo();
    std::vector<Message> getUserMessages();
    std::vector<Course> getUserSetions();
    std::vector<Course> getDepartmentCourses();
    bool userLogIn(QString username, QString password);
    bool addCourse(Course course);
    bool removeCourse(Course course);
    bool createUser(std::vector<QString> userInfo);
    bool editUser(std::vector<QString> userInfo);
    bool sendPrivileges(QString adminUsername, int adminDepartment);
    bool sendMessage(Message message);
    bool decideOnCourse(Course course, bool accepted);
    bool changePassword(QString oldPassword, QString newPassword);
    bool resetPassword(QString userUsername);
    bool addSection(int courseId, int capacity, std::vector<TimeSlot> timeSlots);
    bool editSection(int courseId, int sectionNumber, capacity, std::vector<TimeSlot> timeSlots);



private:
    APIService();
    static APIService* service;
    ClientInterface client;
};

#endif // APISERVICE_H
