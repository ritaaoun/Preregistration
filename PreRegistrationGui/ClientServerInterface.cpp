#include "ClientServerInterface.hpp"

const std::string ClientServerInterface::DELIMITER(",:,");
const std::string ClientServerInterface::FUNC_DELIMITER(":,::,:");
const std::string ClientServerInterface::LIST_DELIMITER("::,,::");
const std::string ClientServerInterface::TIMESLOT_DELIMITER("||::||");
const std::string ClientServerInterface::LIST_TIMESLOT_DELIMITER("|:,:|");

std::vector<std::string> ClientServerInterface::split(const std::string & s, std::string delim)
{
	std::vector<std::string> elems;

	if (delim.size() == 0)
	{
		elems.push_back(s);
	}
	else {
		std::string lastElement;
		for (unsigned int i = 0; i < static_cast<int>(s.length()); i = i + static_cast<int>(lastElement.length()) + static_cast<int>(delim.length())) {
			lastElement = s.substr(i, s.find(delim, i)-i);
			elems.push_back(lastElement);
		}
	}
	return elems;
}