#include "message.h"

Message::Message()
{

}

QString Message::getFrom()
{
    return mFrom;
}

std::string Message::getFromStdString()
{
    return mFrom.toStdString();
}

QString Message::getTo()
{
    return mTo;
}

std::string Message::getToStdString()
{
    return mTo.toStdString();
}

QString Message::getMessage()
{
    return mMessage;
}

std::string Message::getMessageStdString()
{
    return mMessage.toStdString();
}

QString Message::getSubject()
{
    return mSubject;
}

std::string Message::getSubjectStdString()
{
    return mSubject.toStdString();
}

void Message::setFrom(QString from)
{
    mFrom = from;
}

void Message::setFrom(std::string from)
{
    mFrom = QString::fromStdString(from);
}

void Message::setTo(QString to)
{
    mTo = to;
}

void Message::setTo(std::string to)
{
    mTo = QString::fromStdString(to);
}

void Message::setMessage(QString message)
{
    mMessage = message;
}

void Message::setMessage(std::string message)
{
    mMessage = QString::fromStdString(message);
}

void Message::setSubject(QString subject)
{
    mSubject = subject;
}

void Message::setSubject(std::string subject)
{
    mSubject = QString::fromStdString(subject);
}
