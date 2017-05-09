#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 8192
#define DEFAULT_PORT "27015"


class NetworkClient {
public:
	NetworkClient();
	~NetworkClient();
	NetworkClient(const NetworkClient & other);
	NetworkClient & operator=(const NetworkClient & rhs);
	std::string sendData(std::string params);
	void closeConnection();

private:

	void connectClient();


	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	std::string sendbuf = "this is a test";
	int iResult;
	int iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;
};
