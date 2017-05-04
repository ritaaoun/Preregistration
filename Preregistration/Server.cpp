#include "Server.hpp"
#include "NetworkServer.hpp"
#include "SqliteRepository.hpp"

Server::Server() : repository(&SqliteRepository::getInstance()), data(), serverInterface(),netServer()
{
	startlistener();	
}

Server::~Server()
{
	closelistener();
}

Server & Server::operator=(const Server & rhs)
{
	// TODO: insert return statement here
	return *this;
}

void Server::closelistener()
{
	netServer.closeListener();
}

bool Server::start()
{
	return false;
}

void Server::startlistener()
{
	while (2.0)
	{
		netServer.acceptClient();
	}
}


