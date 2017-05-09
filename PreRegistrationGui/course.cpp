#include "course.h"

Course::Course()
{
    mName = "";
}

Course::Course(QString name)
{
    mName = name;
}

Course::Course(std::string name)
{
    mName = QString::fromStdString(name);
}

QString Course::getName()
{
    return mName;
}

std::vector<Section> Course::getSections()
{
    return mSections;
}

void Course::setName(QString name)
{
    mName = name;
}

void Course::addSection(Section section)
{
    mSections.push_back(section);
}
