#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <user.h>
#include <unordered_map>
#include <vector>
#include <ClientInterface.hpp>
#include "userinfo.h"
#include "message.h"

class Parser
{
public:
    Parser();

    static std::vector<std::string> getStdVector(std::vector<QString> qStringVector);

    static std::string sendActiveUser();
    static std::string sendCredentials(std::string username, std::string password);
    static std::string sendCreateUserInfo(std::string admin, std::vector<std::string> userInfo);
    static std::string sendMessage(Message message);

    static void getCreateUser(std::string message);
    static bool getBoolean(std::string message);
    static std::unordered_map<int, QString>  getDepartments(std::string message);
    static std::vector<UserInfo> getAdminUserInfo(std::string message);
    static std::vector<Message> getUserMessages(std::string message);
};

#endif // PARSER_H
