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
Commands Command::getCommandByStroke(char *command, bool haveParams)
{
	if (haveParams)
	{
		char * pch = strtok(command, " -");
		if (pch != NULL)
			command = pch;
	}
		
	if (!strcmp(command, "connect"))
		return CONNECT;
	else if (!strcmp(command, "disconnect"))
		return DISCONNECT;
	else if (!strcmp(command, "mkdir"))
		return MAKE_DIR;
	else if (!strcmp(command, "cdir"))
		return CURRENT_DIR;
	else if (!strcmp(command, "rmdir"))
		return DELETE_DIR;
	else if (!strcmp(command, "cd"))
		return CHANGE_DIR;
	else if (!strcmp(command, "help"))
		return HELP;
	else if (!strcmp(command, "clear"))
		return CLEAR_CONSOLE;
	else if (!strcmp(command, "exit"))
		return EXIT;
	else
		return COMMAND_ERROR;
		
}
char * Command::getCommandLineArguments(char *cmd)
{
	char *arguments = new char[2];
	arguments[0] = '\0';

	char *commandLine = new char[strlen(cmd) + 1];
	strcpy_s(commandLine, strlen(cmd) + 1, cmd);

	char *pch = strtok(commandLine, " -=");
	pch = strtok(NULL, " -=");

	while (pch != NULL)
	{
		int length = strlen(arguments) + strlen(pch) + 1;
		
		arguments = (char *)realloc(arguments, length + 1);
		strcat_s(arguments, length, pch);
		
		pch = strtok(NULL, " -=");	

		if (pch != NULL)
		{
			arguments = (char *)realloc(arguments, strlen(arguments) + 2);
			strcat_s(arguments, strlen(arguments) + 2, ",");
		}
	}

	return arguments;
}