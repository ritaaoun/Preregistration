#include "Server.hpp"
#include "NetworkServer.hpp"
#include "SqliteRepository.hpp"

Server::Server() : repository(&SqliteRepository::getInstance()), data(), serverInterface(),netServer()
{
}

Server::~Server()
{
	closelistener();
}

Server & Server::operator=(const Server & rhs)
{
	return *this;
}

void Server::closelistener()
{
	netServer.closeListener();
}

bool Server::start()
{
	data.initialize();
	startlistener();
	return true;
}

void Server::startlistener()
{
	while (2.0)
	{
		netServer.startListener();
		netServer.acceptClient();
	}
}


