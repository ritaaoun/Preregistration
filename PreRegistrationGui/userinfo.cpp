#include "userinfo.h"

UserInfo::UserInfo()
{

}

void UserInfo::setId(int id)
{
    mId = id;
}

void UserInfo::setFirstName(QString firstName)
{
    mFirstName = firstName;
}

void UserInfo::setLastName(QString lastName)
{
    mLastName = lastName;
}

void UserInfo::setMiddleName(QString middleName)
{
    mMiddleName = middleName;
}

void UserInfo::setUsername(QString username)
{
    mUsername = username;
}

void UserInfo::setDedepartment(int department)
{
    mDepartment = department;
}

void UserInfo::setDateOfBirth(QDate dob)
{
    mDateOfBirth = dob;
}

void UserInfo::setStartYear(int startYear)
{
    mStartYear = startYear;
}

void UserInfo::setStartTerm(int startTerm)
{
    mStartTerm = startTerm;
}

void UserInfo::setUserType(int userType)
{
    mUserType = userType;
}

int UserInfo::getId()
{
    return mId;
}

QString UserInfo::getFirstName()
{
    return mFirstName;
}

std::string UserInfo::getFirstNameStdString()
{
    return mFirstName.toStdString();
}

QString UserInfo::getMiddleName()
{
    return mMiddleName;
}

std::string UserInfo::getMiddleNameStdString()
{
    return mMiddleName.toStdString();
}

QString UserInfo::getLastName()
{
    return mLastName;
}

std::string UserInfo::getLastNameStdString()
{
    return mLastName.toStdString();
}

QString UserInfo::getUsername()
{
    return mUsername;
}

int UserInfo::getDepartment()
{
    return mDepartment;
}

QDate UserInfo::getDateOfBirth()
{
    return mDateOfBirth;
}

int UserInfo::getStartYear()
{
    return mStartYear;
}

int UserInfo::getStartTerm()
{
    return mStartTerm;
}

int UserInfo::getUserType()
{
    return mUserType;
}
