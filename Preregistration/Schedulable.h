#pragma once
#include<vector>
//using namespace std;

class Section;

class Schedulable 
{
public:
	virtual const std::vector<Section *> getSections() = 0;
};