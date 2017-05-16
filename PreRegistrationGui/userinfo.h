#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <QDate>

class UserInfo
{
public:
    UserInfo();

    void setId(int id);
    void setFirstName(QString firstName);
    void setMiddleName(QString lastName);
    void setLastName(QString middleName);
    void setUsername(QString username);
    void setDedepartment(int department);
    void setDateOfBirth(QDate dob);
    void setStartYear(int startYear);
    void setStartTerm(int startTerm);
    void setUserType(int userType);

    int getId();
    QString getFirstName();
    std::string getFirstNameStdString();
    QString getMiddleName();
    std::string getMiddleNameStdString();
    QString getLastName();
    std::string getLastNameStdString();
    QString getUsername();
    int getDepartment();
    QDate getDateOfBirth();
    int getStartYear();
    int getStartTerm();
    int getUserType();

private:
    int mId;
    QString mFirstName;
    QString mMiddleName;
    QString mLastName;
    QString mUsername;
    int mDepartment;
    QDate mDateOfBirth;
    int mStartYear;
    int mStartTerm;
    int mUserType;
};

#endif // USERINFO_H
