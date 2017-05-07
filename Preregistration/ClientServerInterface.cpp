#include "ClientServerInterface.hpp"

const std::string ClientServerInterface::DELIMITER(",:,");
const std::string ClientServerInterface::FUNC_DELIMITER(":,:,:");

std::vector<std::string> ClientServerInterface::split(const std::string & s, std::string delim)
{
	std::vector<std::string> elems;

	if (delim.size() == 0)
	{
		elems.push_back(s);
	}
	else {
		std::string lastElement;
		for (int i = 0; i < s.length(); i = i + lastElement.length() + delim.length()) {
			lastElement = s.substr(i, s.find(delim, i));
			elems.push_back(lastElement);
		}
	}
	return elems;
}