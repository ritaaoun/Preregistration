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
