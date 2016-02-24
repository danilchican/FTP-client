#pragma comment(lib, "wsock32.lib")

#include <iostream>
#include <Winsock.h>
#include "headers\Command.h"

using namespace std;

void Command::sendCommand(SOCKET sock, const char *command)
{
	int length = strlen(command);
	char *buf = new char[length + 8];

	strcpy_s(buf, length + 1, command);
	strcat_s(buf, 7, "\r\n");

	try
	{
		int backed_code = send(sock, buf, strlen(buf), 0);
		if (backed_code <= 0)
			throw backed_code;
	}
	catch (int code)
	{
		switch (code)
		{
		case 0:
			cout << "Cannot send command. Connection closed..." << endl;
			break;
		case -1:
			cout << "Cannot send command. Connection failed..." << endl;
			break;
		default:
			cout << "Something error: " << WSAGetLastError() << endl;
			break;
		}
	}
	catch (...)
	{
		cout << "Something error: " << WSAGetLastError() << endl;
	}
	
}
