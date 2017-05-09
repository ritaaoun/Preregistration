#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <user.h>
#include <unordered_map>
#include <vector>
#include <ClientInterface.hpp>
#include "userinfo.h"

class Parser
{
public:
    Parser();

    static std::vector<std::string> getStdVector(std::vector<QString> qStringVector);

    static std::string sendCredentials(std::string username, std::string password);
    static std::string sendCreateUserInfo(std::string admin, std::vector<std::string> userInfo);

    static void getCreateUser(std::string message);
    static bool getBoolean(std::string message);
    static std::unordered_map<int, QString>  getDepartments(std::string message);
    static std::vector<UserInfo> getAdminUserInfo(std::string message);
};

#endif // PARSER_H
