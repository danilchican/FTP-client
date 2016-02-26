#include "headers\Headers.h"

using namespace std;

void Command::sendCommand(SOCKET sock, const char *command)
{
	int length = strlen(command);
	char *buffer = new char[length + 3];

	strcpy_s(buffer, length + 1, command);
	strcat_s(buffer, length + 3, "\r\n");

	try
	{
		int backed_code = send(sock, buffer, strlen(buffer), 0);
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
Commands Command::getCommandByStroke(const char *command)
{
	if (!strcmp(command, "connect"))
		return CONNECT;
	else if (!strcmp(command, "disconnect"))
		return DISCONNECT;
	else if (!strcmp(command, "clear"))
		return CLEAR_CONSOLE;
	else
		return COMMAND_ERROR;
}