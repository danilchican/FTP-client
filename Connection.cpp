#include <iostream>
#include "headers\Connection.h"

bool Connection::Connect()
{
	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Error socket: " << WSAGetLastError() << std::endl;
		WSACleanup(); // Reinstalling Winsock library

		return false;
	}

	struct sockaddr_in sockInfo = { AF_INET, htons(port) }; // Set up socket information.

	try
	{
		struct hostent *host = gethostbyname(this->ftpHost); // Get host by name
		
		if (host == NULL)
			throw "Can't find host...";

		std::cout << "gethostbyname = " << host << std::endl;
	
		std::cout << "Host name: " << host->h_name << std::endl;

		sockInfo.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)host->h_addr))); // Get the IP-address of our ftp
	}
	catch (char *error)
	{
		std::cout << "Error: " << error << std::endl;
		return false;
	}
	catch (...)
	{
		std::cout << "Connect error: " << WSAGetLastError() << std::endl;
			return false;
	};
	
	// Server address got, take connection

	if (connect(this->sock, (sockaddr *)&sockInfo, sizeof(sockInfo)))
	{
		std::cout << "Connect error: " << WSAGetLastError() << std::endl;
		return false;
	}

	return true;
}