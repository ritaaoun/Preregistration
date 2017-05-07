#include "Server.hpp"
#include <iostream>

int main()
{
	Server::getInstance();
	Server::getInstance().startlistener();
}