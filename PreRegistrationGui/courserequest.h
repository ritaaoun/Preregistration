#ifndef COURSEREQUEST_H
#define COURSEREQUEST_H

#include <QString>

class CourseRequest
{
private:
    QString mCourseName;
    QString mDepartment;
    QString mProfessor;

public:
    CourseRequest();

    void setCourseName(QString courseName);
    void setDepartment(QString department);
    void setProfessor(QString professor);

    QString getCourseName();
    QString getDepartment();
    QString getProfessor();
};

#endif // COURSEREQUEST_H
