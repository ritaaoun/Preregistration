#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:
    Message();

    QString getFrom();
    std::string getFromStdString();
    QString getTo();
    std::string getToStdString();
    QString getMessage();
    std::string getMessageStdString();
    QString getSubject();
    std::string getSubjectStdString();

    void setFrom(QString from);
    void setFrom(std::string from);
    void setTo(QString to);
    void setTo(std::string to);
    void setMessage(QString message);
    void setMessage(std::string message);
    void setSubject(QString subject);
    void setSubject(std::string subject);

private:
    QString mFrom;
    QString mTo;
    QString mMessage;
    QString mSubject;
};

#endif // MESSAGE_H
