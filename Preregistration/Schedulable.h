#pragma once
#include<list>
using namespace std;

class Section;
class Schedule;

class Schedulable 
{

public:
	virtual const std::list<Section *> & getSections() const = 0;
	//virtual Schedule * getSchedule() = 0;

};