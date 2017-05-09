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
    QString mRoom;
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
};

#endif // SECTION_H
