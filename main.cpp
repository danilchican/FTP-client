#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "wsock32.lib")

#include <stdio.h>
#include <Winsock.h>
#include <windows.h>
#include <iostream>

#include "headers\Connection.h"

#define PORT 21

WSADATA ws;
char buf[256];

int main()
{
	WSAStartup(0x101, &ws); // Initialize the process of wsock32.dll library

	Connection *c1 = new Connection("vh60.hoster.by", PORT); // Create new connection with params (host, port)
	
	if (!c1->Connect()) // Connect to host by socket 
		std::cout << "Cannot connect to host..." << std::endl;
	else
		std::cout << "Connected to host..." << std::endl;	

	c1->CloseConnection(); // Close connection

	WSACleanup(); // Clear filled resources for WinSock

	return 0;
}