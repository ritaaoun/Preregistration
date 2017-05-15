#include "section.h"

Section::Section()
{

}

int Section::getNumber()
{
    return mNumber;
}

int Section::getCapacity()
{
    return mCapacity;
}

int Section::getStudentCount()
{
    return mStudentCount;
}

QString Section::getRoom()
{
    return mRoom;
}

QString Section::getProfessorName()
{
    return mProfessorName;
}

std::vector<TimeSlot> Section::getTimeSlots()
{
    return mSlots;
}

void Section::setNumber(int number)
{
    mNumber = number;
}

void Section::setCapacity(int capacity)
{
    mCapacity = capacity;
}

void Section::setRoom(QString room)
{
    mRoom = room;
}

void Section::setRoom(std::string room)
{
    mRoom = QString::fromStdString(room);
}

void Section::addTimeSlot(TimeSlot slot)
{
    mSlots.push_back(slot);
}

void Section::setCrn(int crn)
{
    mCrn = crn;
}
void Section::setStudentCount(int studentCount)
{
    mStudentCount = studentCount;
}

void Section::setProfessorName(QString professorName)
{
    mProfessorName = professorName;
}

void Section::setProfessorName(std::string professorName)
{
    mProfessorName = QString::fromStdString(professorName);
}
