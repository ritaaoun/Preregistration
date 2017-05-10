#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <vector>
#include "section.h"

class Course
{
private:
    int mId;
    QString mCode;
    QString mName;
    QString mDescription;
    int mCredits;

    std::vector<Section> mSections;

public:
    Course();

    int getId();
    QString getCode();
    std::string getCodeStdString();
    QString getName();
    std::string getNameStdString();
    QString getDescription();
    std::string getDescriptionStdString();
    int getCredits();

    std::vector<Section> getSections();

    void setId(int id);
    void setCode(QString code);
    void setCode(std::string code);
    void setName(QString name);
    void setName(std::string name);
    void setDescription(QString description);
    void setDescription(std::string descrpition);
    void setCredits(int credits);

    void addSection(Section section);
};

#endif // COURSE_H
