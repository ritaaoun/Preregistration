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

    QString mName;
    QString mUsername;
    Type mType;
    int mId;

    User();

public:
   static User* getUser();
   static void removeUser();

   QString getName();
   QString getUsername();
   Type getType();
   int getId();

   void setName(QString name);
   void setName(std::string name);
   void setUsername(QString username);
   void setUsername(std::string username);
   void setType(Type type);
   void setId(int id);

};

#endif // USER_H
