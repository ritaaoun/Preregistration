#pragma once
#include "ServerData.hpp"
#include "AbstractRepository.hpp"
#include "ServerInterface.hpp"
#include "NetworkServer.hpp"
#include <list>
#include <thread>


class Server {
public:
	bool start();

	static Server & getInstance()
	{
		static Server instance;
		return instance;
	}
	//Has all the data
	AbstractRepository * repository;
	ServerData data;
	ServerInterface serverInterface;
	NetworkServer netServer;

protected:
		
	// Server Configuration 
	void startlistener();
	void closelistener();

	//Client Server Interface


private:
	
	Server();
	~Server();
	Server(const Server & other);
	Server & operator=(const Server & rhs);
};