#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <vector>
#include "section.h"

class Course
{
private:
    QString mName;

    std::vector<Section> mSections;

public:
    Course();
    Course(QString name);
    Course(std::string name);

    QString getName();
    std::vector<Section> getSections();

    void setName(QString name);
    void setName(std::string name);
    void addSection(Section section);
};

#endif // COURSE_H
