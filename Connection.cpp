#include "headers\Headers.h"
using namespace std;

Connection::Connection(Database * db) 
{
	strcpy_s(this->ftpHost, 80, db->_hostname());
	this->port = atoi(db->_port());
	strcpy_s(this->login, 80, db->_username());
	strcpy_s(this->password, 80, db->_password());
}
Connection::Connection(const char *ipHost, unsigned int active_port) : port(active_port)
{
	strcpy_s(this->ftpHost, ipHost);
}
bool Connection::connectToServer()
{
	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "Error socket: " << WSAGetLastError() << endl;
		WSACleanup(); // Reinstalling Winsock library

		return false;
	}

	struct sockaddr_in sockInfo = { AF_INET, htons(port) }; // Set up socket information.

	try	{
		struct hostent *host = gethostbyname(this->ftpHost); // Get host by name
		
		if (host == NULL) {
			throw "Can't find host...";
		}

		sockInfo.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)host->h_addr))); // Get the IP-address of our ftp
	}
	catch (char *error)	{
		cout << "Error: " << error << endl;
		return false;
	}
	catch (...)	{
		cout << "Connect error: " << WSAGetLastError() << endl;
			return false;
	};
	
	if (connect(this->sock, (sockaddr *)&sockInfo, sizeof(sockInfo))) { // Server address got, take connection	
		cout << "Connect error: " << WSAGetLastError() << endl;
		return false;
	}

	return true;
}
bool Connection::authorisation()
{
	int length = strlen(login);
	char *userData = new char[length + 7];
	strcpy_s(userData, length + 6, "USER ");
	strcat_s(userData, length + 6, login);

	length = strlen(password);
	char *passData = new char[length + 7];
	strcpy_s(passData, length + 6, "PASS ");
	strcat_s(passData, length + 6, password);
	
	try {
		Command::sendCommand(this->sock, userData); // send login
		this->serverResponse();
		Command::sendCommand(this->sock, passData); // send pass
		this->serverResponse();

		int code = ResponseHandler::getCodeResponse(this->serverResponse());
		ResponseHandler::handler(code);

		return true;
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
		return false;
	}
}
bool Connection::close() // close connection
{
	try	{
		this->quit(); // calling quit() method
		
		this->closeSocket(); // Close current socket

		return true;
	}
	catch (char *message)
	{
		cout << message << endl;
		this->closeSocket(); // Close current socket
		return false;
	}
}
void Connection::quit() // send QUIT command
{
	Command::sendCommand(this->sock, "QUIT");
	int code = ResponseHandler::getCodeResponse(this->serverResponse());
	ResponseHandler::handler(code);
}
char * Connection::serverResponse()
{
	char aa[256] = { '/0' };

	int ii = recv(this->sock, aa, sizeof(aa), 0);
	strcpy_s(this->response, sizeof(aa), aa);

	cout << "Response: " << response << endl;

	return this->response;
}
bool Connection::setPassiveMode()
{
	Command::sendCommand(this->sock, "PASV"); // send login
	return (this->setIPForActiveMode()) ? true : false;
}
bool Connection::setIPForActiveMode()
{
	try	{
		char *string = 0;
		char aa[256] = { '/0' };
		int ii = 0;

		ii = recv(this->sock, aa, sizeof(aa), 0);

		if (string != 0) {
			strcpy_s(string, sizeof(aa), aa);
		}

		if (ii == 0 || ii == -1) {
			throw "Connection lost...";
		}

		cout << "Response: " << aa << endl;

		// extract the sample string "216,92,6,187,194,13"
		char szIP[40];
		char* start = strchr(aa, '(');
		char* end = strchr(aa, ')');
		int num = end - start;

		char str[30] = { '\0' };
		strncpy_s(str, start + 1, num - 1);

		// Lets break the string up using the ',' character as a seperator
		char* token = strtok(str, ","); 

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

		return true;
	}
	catch (char *message)
	{
		cout << message << endl;
	}

	return false;
}
void Connection::closeSocket()
{
	closesocket(this->sock);
}
char * Connection::user()
{
	return this->login;
}
char * Connection::getIPHost()
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