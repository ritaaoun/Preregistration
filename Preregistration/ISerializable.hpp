#pragma once
#include <string>

class ISerializable
{
public:
	virtual std::string serialize() = 0;
	//virtual std::string deserialize() = 0;
};