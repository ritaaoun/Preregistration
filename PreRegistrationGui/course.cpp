#include "course.h"

Course::Course()
{

}

int Course::getId()
{
    return mId;
}

QString Course::getCode()
{
    return mCode;
}

std::string Course::getCodeStdString()
{
    return mCode.toStdString();
}

QString Course::getName()
{
    return mName;
}

std::string Course::getNameStdString()
{
    return mName.toStdString();
}

QString Course::getDescription()
{
    return mDescription;
}

std::string Course::getDescriptionStdString()
{
    return mDescription.toStdString();
}

int Course::getCredits()
{
    return mCredits;
}

std::vector<Section> Course::getSections()
{
    return mSections;
}

void Course::setId(int id)
{
    mId = id;
}

void Course::setCode(QString code)
{
    mCode = code;
}

void Course::setCode(std::string code)
{
    mCode = QString::fromStdString(code);
}

void Course::setName(QString name)
{
    mName = name;
}

void Course::setName(std::string name)
{
    mName = QString::fromStdString(name);
}

void Course::setDescription(QString description)
{
    mDescription = description;
}

void Course::setDescription(std::string descrpition)
{
    mDescription = QString::fromStdString(descrpition);
}

void Course::setCredits(int credits)
{
    mCredits = credits;
}

void Course::addSection(Section section)
{
    mSections.push_back(section);
}

Course & Course::operator=(const Course & that)
{
    this->mId = that.mId;
    this->mCode = that.mCode;
    this->mName = that.mName;
    this->mDescription = that.mDescription;
    this->mCredits = that.mCredits;
    this->mSections = that.mSections;

    return *this;
}
