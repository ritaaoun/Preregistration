#pragma once
#include<vector>
using namespace std;

class Section;
class Schedule;

class Schedulable 
{

public:
	virtual const std::vector<Section *> getSections() = 0;
	//virtual Schedule * getSchedule() = 0;

};