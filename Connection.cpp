#include <iostream>
#include <cstring>
using namespace std;

#include "headers\Connection.h"

Connection::Connection(char *ftpHost, int port) : port(port)
{
	strcpy_s(this->ftpHost, ftpHost);
}
bool Connection::Connect()
{
	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "Error socket: " << WSAGetLastError() << endl;
		WSACleanup(); // Reinstalling Winsock library

		return false;
	}

	struct sockaddr_in sockInfo = { AF_INET, htons(port) }; // Set up socket information.

	try
	{
		struct hostent *host = gethostbyname(this->ftpHost); // Get host by name
		
		if (host == NULL) throw "Can't find host...";
	
		cout << "Host name: " << host->h_name << endl;

		sockInfo.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)host->h_addr))); // Get the IP-address of our ftp
	}
	catch (char *error)
	{
		cout << "Error: " << error << endl;
		return false;
	}
	catch (...)
	{
		cout << "Connect error: " << WSAGetLastError() << endl;
			return false;
	};
	
	if (connect(this->sock, (sockaddr *)&sockInfo, sizeof(sockInfo))) // Server address got, take connection
	{
		cout << "Connect error: " << WSAGetLastError() << endl;
		return false;
	}

	return true;
}
bool Connection::Close() // close connection
{
	// will send QUIT command here 

	this->quit(); // calling quit() method

	closesocket(this->sock); // Close current socket

	return true;
}
void Connection::quit() // send QUIT command
{
	this->sendCommand("QUIT"); 
}
void Connection::sendCommand(const char *command) // send command
{
	int length = strlen(command);
	char *buf = new char[length + 8];

	strcpy_s(buf, length + 1, command);
	strcat_s(buf, 7, "\r\n");

	send(this->sock, buf, strlen(buf), 0);
}