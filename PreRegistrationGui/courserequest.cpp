#include "courserequest.h"

CourseRequest::CourseRequest()
{

}

void CourseRequest::setCourseName(QString courseName)
{
    mCourseName = courseName;
}

void CourseRequest::setDepartment(QString department)
{
    mDepartment = department;
}

void CourseRequest::setProfessor(QString professor)
{
    mProfessor = professor;
}

QString CourseRequest::getCourseName()
{
    return mCourseName;
}

QString CourseRequest::getDepartment()
{
    return mDepartment;
}

QString CourseRequest::getProfessor()
{
    return mProfessor;
}
