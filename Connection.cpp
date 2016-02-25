#include <iostream>
#include <cstring>
using namespace std;

#include "headers\Connection.h"
#include "headers\Command.h"

Connection::Connection() 
{
	cout << "  HOST: ";
	cin >> this->ftpHost;
	cout << "  PORT: ";
	cin >> this->port;
	cout << "  LOGIN: ";
	cin >> this->login;
	cout << "  PASS: ";
	cin >> this->password;

}
Connection::Connection(const char *ftpHost, unsigned int port, const char *login, const char *pass) : port(port)
{
	strcpy_s(this->ftpHost, ftpHost);
	strcpy_s(this->login, login);
	strcpy_s(this->password, pass);
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
	this->quit(); // calling quit() method

	closesocket(this->sock); // Close current socket

	return true;
}
void Connection::quit() // send QUIT command
{
	Command::sendCommand(this->sock, "QUIT");
}
