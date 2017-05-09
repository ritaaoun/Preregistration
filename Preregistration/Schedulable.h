#pragma once
#include<vector>

class Section;

class Schedulable 
{
public:
	virtual const std::vector<Section *> getSections() = 0;
};