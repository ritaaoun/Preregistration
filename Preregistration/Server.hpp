#pragma once
#include "ServerData.hpp"
#include "AbstractRepository.hpp"
#include "ServerInterface.hpp"
#include "myLog.h"
#include "mySocket.h"
#include <vector>
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
	myLog winLog;

protected:
		
	// Server Configuration 
	bool startListener();
	void listen();
	bool closeListener();

	//Client Server Interface


private:

	myTcpSocket myTcpServer;
	std::vector<std::thread> threads;
	const int MAX_THREADS;

	Server();
	~Server();
	Server(const Server & other);
	Server & operator=(const Server & rhs);
};