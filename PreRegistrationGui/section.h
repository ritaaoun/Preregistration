#ifndef SECTION_H
#define SECTION_H

#include <vector>
#include "timeslot.h"

class Section
{
private:
    int mNumber;
    int mCapacity;
    int mCrn;
    int mStudentCount;
    QString mRoom;
    QString mProfessorName;
    std::vector<TimeSlot> mSlots;

public:
    Section();

    int getNumber();
    int getCapacity();
    int getStudentCount();
    QString getRoom();
    QString getProfessorName();
    std::vector<TimeSlot> getTimeSlots();

    void setNumber(int number);
    void setCapacity(int capacity);
    void setRoom(QString room);
    void setRoom(std::string room);
    void addTimeSlot(TimeSlot slot);
    void setCrn(int crn);
    void setStudentCount(int studentCount);
    void setProfessorName(QString professorName);
    void setProfessorName(std::string professorName);
};

#endif // SECTION_H
