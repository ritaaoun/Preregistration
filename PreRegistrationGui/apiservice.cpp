#include "apiservice.h"

APIService* APIService::service = nullptr;

APIService::APIService() : client()
{

}

APIService* APIService::getInstance()
{
    if(service == nullptr)
    {
        service = new APIService();
    }

    return service;
}

std::vector<Course> APIService::getCoursesList()
{
    std::vector<Course> v;

    return v;
}


std::vector<Course> APIService::getUserCourses()
{
    std::vector<Course> v;

    for(int i = 0; i < 1; i++)
    {

    }

    return v;
}

bool APIService::userLogIn(QString username, QString password)
{
    //send info and get response
    std::string toSend = Parser::sendCredentials(username.toStdString(), password.toStdString());
    std::string response = client.login(toSend);

    //CREATE USER here if true
    if(response == "false")
    {
        return false;
    }
    else
    {
        Parser::getCreateUser(response);
    }

    return true;
}

bool APIService::addCourse(Course course)
{
    return true;
}

bool APIService::removeCourse(Course course)
{
    return true;
}

bool APIService::createUser(std::vector<QString> userInfo)
{
    std::vector<std::string> userInfoStdString = Parser::getStdVector(userInfo);
    std::string toSend = Parser::sendCreateUserInfo(User::getUser()->getUsername().toStdString(), userInfoStdString);

    std::string serverResult = client.addUser(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

bool APIService::editUser(std::vector<QString> userInfo)
{
    std::vector<std::string> userInfoStdString = Parser::getStdVector(userInfo);
    std::string toSend = Parser::sendCreateUserInfo(User::getUser()->getUsername().toStdString(), userInfoStdString);

    std::string serverResult = client.editUser(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

std::vector<CourseRequest> APIService::getCourseRequests()
{
    CourseRequest request;
    request.setCourseName("EECE 437");
    request.setDepartment("CCE");
    request.setProfessor("Zizo");

    CourseRequest request2;
    request2.setCourseName("EECE 438");
    request2.setDepartment("CCE");
    request2.setProfessor("Fifo");

    CourseRequest request3;
    request3.setCourseName("EECE 436");
    request3.setDepartment("CCE");
    request3.setProfessor("Fizo");

    std::vector<CourseRequest> requests;
    requests.push_back(request);
    requests.push_back(request2);
    requests.push_back(request3);

    return requests;
}

bool APIService::sendPriviliges(QString adminUsername, QString adminDepartment)
{
    return true;
}

std::unordered_map<int, QString> APIService::getDepartments()
{
    std::string serverResult = client.getDepartments(User::getUser()->getUsername().toStdString());

    std::unordered_map<int, QString> departments = Parser::getDepartments(serverResult);

    return departments;
}

std::vector<UserInfo> APIService::getAdminUsersInfo()
{
    std::string serverResult = client.getUsers(User::getUser()->getUsername().toStdString());

    std::vector<UserInfo> userInfo = Parser::getAdminUserInfo(serverResult);

    return userInfo;
}
