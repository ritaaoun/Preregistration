#include "Server.hpp"
#include "myHostInfo.h"
#include "SqliteRepository.hpp"

Server::Server() : MAX_THREADS(10), repository(&SqliteRepository::getInstance()), data(), serverInterface()
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

bool Server::closelistener()
{
	for (int i = 0;i < MAX_THREADS;i++)
	{
		threads[i].join();
	}
	return true;
}

bool Server::start()
{
	return false;
}

bool Server::startlistener()
{
	winLog << endl;
	winLog << "Retrieve the local host name and address:" << endl;

	myHostInfo uHostAddress;
	string localHostName = uHostAddress.getHostName();
	string localHostAddr = uHostAddress.getHostIPAddress();

	winLog << "		==> Name: " << localHostName << endl;
	winLog << "		==> Address: " << localHostAddr << endl;

	// open socket on the local host
	myTcpServer = myTcpSocket(PORTNUM);
	winLog << "server configuation: " << endl;
	winLog << myTcpServer;

	myTcpServer.bindSocket();
	winLog << endl << "server finishes binding process... " << endl;

	myTcpServer.listenToClient();
	winLog << "server is listening to the port ... " << endl;

	// wait to accept a client connection.  
	// processing is suspended until the client connects
	winLog << "server is waiting for client connnection ... " << endl;

	
	for (int i = 0;i < MAX_THREADS;i++)
	{
		//threads[i] = std::thread(&listen,this);
	}

	return true;
}


void Server::listen()
{
	while (2.0) 
	{
		myTcpSocket* client;    // connection dedicated for client communication
		string clientHost;      // client name etc. 

		client = myTcpServer.acceptClient(clientHost);

		winLog << endl << "==> A client from [" << clientHost << "] is connected!" << endl << endl;

		while (1)
		{
			string clientMessageIn = "";
			string result = "";

			// receive from the client

			int numBytes = client->receiveMessage(clientMessageIn);
			if (numBytes == -99) break;

			result = serverInterface.callFunction(clientMessageIn);

			// send to the client		
			client->sendMessage(result);
		}
	}
}