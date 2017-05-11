#ifndef SECTION_H
#define SECTION_H

#include <vector>
#include "timeslot.h"

class Section
{
private:
    int mNumber;
    int mCapacity;
    int mActual;
    int mCrn;
    int mStudentCount;
    QString mRoom;
    QString mProfessorName;
    std::vector<TimeSlot> mSlots;


public:
    Section();

    int getNumber();
    int getCapacity();
    int getActual();
    QString getRoom();
    std::vector<TimeSlot> getTimeSlots();

    void setNumber(int number);
    void setCapacity(int capacity);
    void setActual(int actual);
    void setRoom(QString room);
    void setRoom(std::string room);
    void addTimeSlot(TimeSlot slot);
    void setCrn(int crn);
    void setStudentCount(int studentCount);
    void setProfessorName(QString mProfessorName);
};

#endif // SECTION_H
