#include "headers\Headers.h"
using namespace std;

Connection::Connection() 
{
	cout << "  HOST: ";
	strcpy_s(this->ftpHost, 80, Checkout<char *>::stroke());
	cout << "  PORT: ";
	this->port = Checkout<unsigned int>::integer(0, 8080);
	cout << "  USER: ";
	strcpy_s(this->login, 80, Checkout<char *>::stroke());
	cout << "  PASS: ";
	strcpy_s(this->password, 80, Checkout<char *>::stroke());
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
		
		if (host == NULL) 
			throw "Can't find host...";
	
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
bool Connection::Authorisation()
{
	int length = strlen(login);
	char *userData = new char[length + 7];
	strcpy_s(userData, length + 6, "USER ");
	strcat_s(userData, length + 6, login);

	length = strlen(password);
	char *passData = new char[length + 7];
	strcpy_s(passData, length + 6, "PASS ");
	strcat_s(passData, length + 6, password);

	Command::sendCommand(this->sock, userData); // send login
	this->ServerResponse();
	Command::sendCommand(this->sock, passData); // send pass
	this->ServerResponse();
	this->ServerResponse();

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
	this->ServerResponse();
}
void Connection::ServerResponse()
{
	char *string = 0;
	char aa[256] = { '/0' };

	int ii = recv(this->sock, aa, sizeof(aa), 0);
	if (string != 0)
		strcpy_s(string,sizeof(aa), aa);

	cout << "Response: " << aa << endl;
}
void Connection::SetPassiveMode()
{
	Command::sendCommand(this->sock, "PASV"); // send login
	this->ServerResponse();
}
char * Connection::user()
{
	return this->login;
}