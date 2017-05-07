#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <vector>

#define DEFAULT_BUFLEN 8192
#define DEFAULT_PORT "27015"


class NetworkServer {

public:
	 NetworkServer();
	~NetworkServer();
	NetworkServer(const NetworkServer & other);
	NetworkServer & operator=(const NetworkServer & rhs);
	int acceptClient();
	void startListener();
	void closeListener();

private:

	std::vector<std::thread> threads;
	const int MAX_THREADS = 10;

	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
};
