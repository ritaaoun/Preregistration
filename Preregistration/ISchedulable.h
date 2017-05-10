#pragma once
#include<vector>

class Section;

class ISchedulable 
{
public:
	virtual const std::vector<Section *> getSections() = 0;
};