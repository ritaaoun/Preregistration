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

int Section::getActual()
{
    return mActual;
}

QString Section::getRoom()
{
    return mRoom;
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

void Section::setActual(int actual)
{
    mActual = actual;
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
