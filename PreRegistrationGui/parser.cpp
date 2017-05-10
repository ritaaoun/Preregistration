#include "parser.h"
#include <QDebug>

Parser::Parser()
{

}


std::vector<std::string> Parser::getStdVector(std::vector<QString> qStringVector)
{
    std::vector<std::string> stringVector;

    for(int i = 0; i < qStringVector.size(); i++)
    {
        stringVector.push_back(qStringVector[i].toStdString());
    }

    return stringVector;
}

std::string Parser::sendActiveUser()
{
    return User::getUser()->getUsername().toStdString();
}

std::string Parser::sendCredentials(std::string username, std::string password)
{
    std::string result;

    result = username + ClientServerInterface::DELIMITER + password;

    return result;
}

void Parser::getCreateUser(std::string message)
{
    //split
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::DELIMITER);

    User::getUser()->setUsername(messageVector[0]);
    User::getUser()->setId(std::stoi(messageVector[1]));
    User::getUser()->setName(messageVector[2] + " " + messageVector[3] + " " + messageVector[4]);

    std::string type = messageVector[5];

    if(type == "2")
    {
        User::getUser()->setType(User::Type::ADMINISTRATOR);
    }
    else if (type == "1")
    {
        User::getUser()->setType(User::Type::PROFESSOR);
    }
    else if (type == "0")
    {
        User::getUser()->setType(User::Type::STUDENT);
    }
}

bool Parser::getBoolean(std::string message)
{
    if(message == "true")
    {
        return true;
    }

    return false;
}

std::string Parser::sendCreateUserInfo(std::string admin, std::vector<std::string> userInfo)
{
    std::string result = admin;

    for(int i = 0; i < userInfo.size(); i++)
    {
        result += ClientServerInterface::DELIMITER + userInfo[i];
    }

    return result;
}

std::unordered_map<int, QString> Parser::getDepartments(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::unordered_map<int, QString> map;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        map[std::stoi(object[0])] = QString::fromStdString(object[1]);
    }

    return map;
}

std::vector<UserInfo> Parser::getAdminUserInfo(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::vector<UserInfo> userInfo;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        UserInfo user;
        user.setUsername(QString::fromStdString(object[0]));
        user.setFirstName(QString::fromStdString(object[1]));
        user.setMiddleName(QString::fromStdString(object[2]));
        user.setLastName(QString::fromStdString(object[3]));
        user.setDedepartment(std::stoi(object[4]));
        user.setDateOfBirth(QDate::fromString(QString::fromStdString(object[5])));
        user.setStartYear(std::stoi(object[6]));
        user.setStartTerm(std::stoi(object[7]));

        userInfo.push_back(user);
    }

    return userInfo;
}

std::vector<Message> Parser::getUserMessages(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::vector<Message> userMessages;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        Message message;

        message.setFrom(object[0]);
        message.setTo(object[1]);
        message.setSubject(object[2]);
        message.setMessage(object[3]);

        userMessages.push_back(message);
    }

    return userMessages;
}

std::string Parser::sendMessage(Message message)
{
    std::string result;

    result = message.getFromStdString()
            + ClientInterface::DELIMITER + message.getToStdString()
            + ClientInterface::DELIMITER + message.getSubjectStdString()
            + ClientInterface::DELIMITER + message.getMessageStdString();

    return result;
}

std::string Parser::sendPrivilges(std::string username, std::string adminUsername, std::string department)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + adminUsername
            + ClientInterface::DELIMITER + department;

    return result;
}

std::vector<Course> Parser::getCourseRequests(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::vector<Course> courses;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        Course course;
        course.setId(stoi(object[0]));
        course.setCode(object[1]);
        course.setName(object[2]);
        course.setDescription(object[3]);
        course.setCredits(stoi(object[4]));

        courses.push_back(course);
    }

    return courses;
}

std::string Parser::sendDecideOnCourse(std::string username, int id, bool accepted)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + std::to_string(id)
            + ClientInterface::DELIMITER + std::to_string(accepted);

    return result;
}

std::string Parser::sendChangePassword(std::string username, std::string oldPassowrd, std::string newPassword)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + oldPassowrd
            + ClientInterface::DELIMITER + newPassword;

    return result;
}

std::string Parser::sendResetPassword(std::string username, std::string userUsername)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + userUsername;

    return result;
}
