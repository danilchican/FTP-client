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
Connection::Connection(const char *ipHost, unsigned int active_port) : active_port(active_port)
{
	strcpy_s(this->ftpHost, ipHost);
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
	
	try
	{
		Command::sendCommand(this->sock, userData); // send login
		this->ServerResponse();
		Command::sendCommand(this->sock, passData); // send pass
		this->ServerResponse();

		int code = ResponseHandler::getCodeResponse(this->ServerResponse());
		// cout << "code: " << code << endl;
		ResponseHandler::handler(code);

		return true;
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
		return false;
	}
}
bool Connection::Close() // close connection
{
	try
	{
		this->quit(); // calling quit() method
		
		closesocket(this->sock); // Close current socket

		return true;
		
	}
	catch (char *message)
	{
		cout << message << endl;
		closesocket(this->sock); // Close current socket
		return false;
	}
}
void Connection::quit() // send QUIT command
{
	Command::sendCommand(this->sock, "QUIT");
	int code = ResponseHandler::getCodeResponse(this->ServerResponse());
	ResponseHandler::handler(code);
}
char * Connection::ServerResponse()
{
	char aa[256] = { '/0' };

	int ii = recv(this->sock, aa, sizeof(aa), 0);
	strcpy_s(this->response, sizeof(aa), aa);

	cout << "Response: " << response << endl;

	return this->response;
}
void Connection::SetPassiveMode()
{
	Command::sendCommand(this->sock, "PASV"); // send login
	this->SetIPForActiveMode();
}
void Connection::SetIPForActiveMode()
{
	char *string = 0;
	char aa[256] = { '/0' };

	int ii = recv(this->sock, aa, sizeof(aa), 0);
	if (string != 0)
		strcpy_s(string, sizeof(aa), aa);

	cout << "Response: " << aa << endl;

	// Lets extract the string "216,92,6,187,194,13"
	char szIP[40];
	char* start = strchr(aa, '(');
	char* end = strchr(aa, ')');
	int num = end - start;

	char str[30] = { '\0' };
	strncpy_s(str, start + 1, num - 1);

	// str now contains "216,92,6,187,194,13"
	char* token = strtok(str, ",");

	// Lets break the string up using the ',' character as a seperator
	// Lets get the IP address from the string.
	strcpy(szIP, "");
	strcat(szIP, token);
	strcat(szIP, ".");  //szIP contains "216."

	token = strtok(NULL, ",");
	strcat(szIP, token);
	strcat(szIP, ".");  //szIP contains "216.92."

	token = strtok(NULL, ",");
	strcat(szIP, token);
	strcat(szIP, "."); // szIP contains "216.92.6."

	token = strtok(NULL, ",");
	strcat(szIP, token);// szIP contains "216.92.6.187"

	// Now lets get the port number
	token = strtok(NULL, ",");
	int intA = atoi(token);  // 194

	token = strtok(NULL, ",");
	int intB = atoi(token);  // 13

	strcpy(this->ipHost, szIP);
	this->active_port = (intA * 256) + intB;
}
char * Connection::user()
{
	return this->login;
}
char * Connection::IPHost()
{
	return this->ipHost;
}
unsigned int Connection::activePort()
{
	return this->active_port;
}
SOCKET Connection::getSock()
{
	return this->sock;
}