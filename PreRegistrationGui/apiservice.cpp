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
    std::string serverResult = client.login(toSend);

    //CREATE USER here if true
    if(serverResult != "false")
    {
        Parser::getCreateUser(serverResult);

        //TEMP
        User::getUser()->setType(User::Type::PROFESSOR);

        return true;
    }

    return false;
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
    std::string toSend = Parser::sendCreateUserInfo(Parser::sendActiveUser(), userInfoStdString);

    std::string serverResult = client.addUser(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

bool APIService::editUser(std::vector<QString> userInfo)
{
    std::vector<std::string> userInfoStdString = Parser::getStdVector(userInfo);
    std::string toSend = Parser::sendCreateUserInfo(Parser::sendActiveUser(), userInfoStdString);

    std::string serverResult = client.editUser(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

std::vector<Course> APIService::getCourseRequests()
{   
    std::string serverResult = client.getCourseRequests(Parser::sendActiveUser());

    std::vector<Course> requests = Parser::getCourseRequests(serverResult);

    return requests;
}

bool APIService::sendPrivileges(QString adminUsername, int adminDepartment)
{
    std::string toSend = Parser::sendPrivilges(Parser::sendActiveUser(), adminUsername.toStdString(), QString::number(adminDepartment).toStdString());

    std::string serverResult = client.givePrivileges(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

std::unordered_map<int, QString> APIService::getDepartments()
{
    std::string serverResult = client.getDepartments(Parser::sendActiveUser());

    std::unordered_map<int, QString> departments = Parser::getDepartments(serverResult);

    return departments;
}

std::vector<UserInfo> APIService::getAdminUsersInfo()
{
    std::string serverResult = client.getUsers(Parser::sendActiveUser());

    std::vector<UserInfo> userInfo = Parser::getAdminUserInfo(serverResult);

    return userInfo;
}

std::vector<Message> APIService::getUserMessages()
{
    std::string serverResult = client.getReceivedMessages(Parser::sendActiveUser());

    std::vector<Message> messagesReceived = Parser::getUserMessages(serverResult);

    serverResult = client.getSentMessages(Parser::sendActiveUser());

    std::vector<Message> messagesSent = Parser::getUserMessages(serverResult);

    std::vector<Message> messages;
    for(int i = 0; i < messagesSent.size(); i++)
        messages.push_back(messagesSent[i]);
    for(int i = 0; i< messagesReceived.size(); i++)
        messages.push_back(messagesReceived[i]);

    return messages;
}

bool APIService::sendMessage(Message message)
{
    std::string toSend = Parser::sendMessage(message);

    std::string serverResult = client.sendMessage(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

bool APIService::decideOnCourse(Course course, bool accepted)
{
    std::string toSend = Parser::sendDecideOnCourse(Parser::sendActiveUser(), course.getId(), accepted);

    std::string serverResult = client.decideOnCourse(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

bool APIService::changePassword(QString oldPassword, QString newPassword)
{
    std::string toSend = Parser::sendChangePassword(Parser::sendActiveUser(), oldPassword.toStdString(), newPassword.toStdString());

    std::string serverResult = client.changePassword(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

bool APIService::resetPassword(QString userUsername)
{
    std::string toSend = Parser::sendResetPassword(Parser::sendActiveUser(), userUsername.toStdString());

    std::string serverResult = client.resetPassword(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

bool APIService::addSection(int courseId, int capacity, timeSlots)
{
    std::string toSend = Parser::sendAddSection(Parser::sendActiveUser(), courseId, capacity, timeSlots);

    std::string serverResult = client.addSection(toSend);

    bool result = Parser::getBoolean(serverResult);

    return result;
}

std::vector<Course> APIService::getUserSetions()
{
    std::string serverResult = client.getUserSections(Parser::sendActiveUser());

    std::vector<Course> result = Parser::getSections(serverResult);

    return result;
}

std::vector<Course> APIService::getDepartmentCourses()
{
    std::string serverResult = client.getUserDepartmentSections(Parser::sendActiveUser());

    std::vector<Course> result = Parser::getSections(serverResult);

    return result;
}
