#include "headers\Headers.h"

int main()
{
	WSAStartup(0x101, &ws); // Initialize the process of wsock32.dll library

	Connection *c1 = new Connection("vh60.hoster.by", PORT); // Create new connection with params (host, port)
	
	if (!c1->Connect()) // Connect to host by socket 
		std::cout << "Cannot connect to host..." << std::endl;
	else
		std::cout << "Connected to host..." << std::endl;	

	c1->Close(); // Close connection

	WSACleanup(); // Clear filled resources for WinSock

	return 0;
}