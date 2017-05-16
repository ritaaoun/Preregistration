#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    enum Type{
        ADMINISTRATOR, PROFESSOR, STUDENT
    };

private:
    static User* mUser;

    QString mUsername;
    int mId;
    QString mName;
    int mDepartmentId;
    QString mBirthday;
    QString mStartYear;
    QString mStartTerm;
    Type mType;


    User();

public:
   static User* getUser();
   static void removeUser();

   int getId();
   QString getUsername();
   QString getName();
   int getDepartmentId();
   QString getBirthday();
   QString getStartYear();
   QString getStartTerm();
   Type getType();

   void setName(QString name);
   void setName(std::string name);
   void setUsername(QString username);
   void setUsername(std::string username);
   void setBirthday(QString birthday);
   void setBirthday(std::string birthday);
   void setDepartmentId(int departmentId);
   void setStartYear(QString startYear);
   void setStartYear(std::string startYear);
   void setStartTerm(QString startTerm);
   void setStartTerm(std::string startTerm);
   void setType(Type type);
   void setId(int id);
};

#endif // USER_H
