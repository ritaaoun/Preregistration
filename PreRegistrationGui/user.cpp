#include "user.h"

User* User::mUser = nullptr;

User::User()
{

}

User* User::getUser()
{
    if(mUser == nullptr)
        mUser = new User();

    return mUser;
}

QString User::getName()
{
    return mName;
}

QString User::getUsername()
{
    return mUsername;
}

User::Type User::getType()
{
    return mType;
}

int User::getId()
{
    return mId;
}

void User::setName(QString name)
{
    mName = name;
}

void User::setName(std::string name)
{
    mName = QString::fromStdString(name);
}

void User::setUsername(QString username)
{
    mUsername = username;
}

void User::setUsername(std::string username)
{
    mUsername = QString::fromStdString(username);
}

void User::setType(Type type)
{
    mType = type;
}

void User::setId(int id)
{
    mId = id;
}
