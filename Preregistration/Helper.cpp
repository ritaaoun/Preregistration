#include "Helper.hpp"
#include <iostream>

long Helper::stringToLong(const std::string & nb)
{
	char *end;
	errno = 0;
	long l = std::strtol(nb.c_str(), &end, 0);
	if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
		std::cerr << "SqliteRepository::stringToLong: overflow when converting " + nb << std::endl;
		return 0;
	}
	if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
		std::cerr << "SqliteRepository::stringToLong: underflow when converting " + nb << std::endl;
		return 0;
	}
	if (nb.c_str() == '\0' || *end != '\0') {
		std::cerr << "SqliteRepository::stringToLong: " + nb + " is unconvertable" << std::endl;
		return 0;
	}

	return l;
}
