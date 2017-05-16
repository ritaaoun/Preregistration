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

void User::removeUser()
{
    if(mUser)
    {
        delete mUser;
        mUser = nullptr;
    }
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

int User::getDepartmentId()
{
    return mDepartmentId;
}

QString User::getBirthday()
{
    return mBirthday;
}

QString User::getStartYear()
{
    return mStartYear;
}

QString User::getStartTerm()
{
    return mStartTerm;
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

void User::setBirthday(QString birthday)
{
    mBirthday = birthday;
}

void User::setBirthday(std::string birthday)
{
    mBirthday = QString::fromStdString(birthday);
}

void User::setStartYear(QString startYear)
{
    mStartYear = startYear;
}

void User::setStartYear(std::string startYear)
{
    mStartYear = QString::fromStdString(startYear);
}

void User::setStartTerm(QString startTerm)
{
    mStartTerm = startTerm;
}

void User::setStartTerm(std::string startTerm)
{
    mStartTerm = QString::fromStdString(startTerm);
}

void User::setDepartmentId(int departmentId)
{
    mDepartmentId = departmentId;
}
