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

class APIService
{
public:
    static APIService* getInstance();

    std::vector<Course> getCoursesList();
    std::vector<Course> getUserCourses();
    std::vector<CourseRequest> getCourseRequests();
    std::unordered_map<int, QString> getDepartments();
    std::vector<UserInfo> getAdminUsersInfo();
    bool userLogIn(QString username, QString password);
    bool addCourse(Course course);
    bool removeCourse(Course course);
    bool createUser(std::vector<QString> userInfo);
    bool editUser(std::vector<QString> userInfo);
    bool sendPriviliges(QString adminUsername, QString adminDepartment);

private:
    APIService();
    static APIService* service;
    ClientInterface client;
};

#endif // APISERVICE_H
