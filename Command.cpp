#include "headers\Headers.h"

using namespace std;

void Command::sendCommand(SOCKET sock, const char *command)
{
	int length = strlen(command);
	char *buffer = new char[length + 3];

	strcpy_s(buffer, length + 1, command);
	strcat_s(buffer, length + 3, "\r\n");

	try	{
		int backed_code = send(sock, buffer, strlen(buffer), 0);
		
		if (backed_code <= 0) {
			throw backed_code;
		}
	}
	catch (int code)
	{
		switch (code) {
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
Commands Command::getCommandByStroke(char *comm, bool haveParams)
{
	char *command = new char[strlen(comm) + 1];
	strcpy_s(command, strlen(comm) + 1, comm);

	if (haveParams)	{
		char * pch = strtok(command, " ");

		if (pch != NULL) {
			command = pch;
		}
	}
		
	if (!strcmp(command, "create"))
		return CONNECT;
	else if (!strcmp(command, "close"))
		return DISCONNECT;
	else if (!strcmp(command, "mkdir"))
		return MAKE_DIR;
	else if (!strcmp(command, "pwd"))
		return CURRENT_DIR;
	else if (!strcmp(command, "up"))
		return MOVE_UP;
	else if (!strcmp(command, "rmdir"))
		return DELETE_DIR;
	else if (!strcmp(command, "rm"))
		return DELETE_FILE;
	else if (!strcmp(command, "rn"))
		return RENAME_FILE;
	else if (!strcmp(command, "hosts"))
		return HOSTS;
	else if (!strcmp(command, "addhost"))
		return ADD_HOST;
	else if (!strcmp(command, "rmhost"))
		return DELETE_HOST;
	else if (!strcmp(command, "download"))
		return DOWNLOAD_FILE;
	else if (!strcmp(command, "upload"))
		return UPLOAD_FILE;
	else if (!strcmp(command, "ls"))
		return LIST;
	else if (!strcmp(command, "cd"))
		return CHANGE_DIR;
	else if (!strcmp(command, "help"))
		return HELP;
	else if (!strcmp(command, "clear"))
		return CLEAR_CONSOLE;
	else if (!strcmp(command, "exit"))
		return EXIT;
	else {
		return COMMAND_ERROR;
	}
		
}
char * Command::getCommandLineArguments(char *cmd)
{
	char *arguments = new char[2];
	arguments[0] = '\0';

	char *commandLine = new char[strlen(cmd) + 1];
	strcpy_s(commandLine, strlen(cmd) + 1, cmd);

	char *pch = strtok(commandLine, " ");
	pch = strtok(NULL, " ");

	while (pch != NULL)	{
		int length = strlen(arguments) + strlen(pch) + 1;
		
		arguments = (char *)realloc(arguments, length + 1);
		strcat_s(arguments, length, pch);
		
		pch = strtok(NULL, " ");	

		if (pch != NULL) {
			arguments = (char *)realloc(arguments, strlen(arguments) + 2);
			strcat_s(arguments, strlen(arguments) + 2, ",");
		}
	}

	return arguments;
}
bool Command::haveAnyArgs(char *cmd)
{
	int countArguments;

	char *commandLine = new char[strlen(cmd) + 1];
	strcpy_s(commandLine, strlen(cmd) + 1, cmd);

	char *pch = strtok(commandLine, " -");

	for (countArguments = -1; pch != NULL; countArguments++) {
		pch = strtok(NULL, " -");
	}

	return (countArguments > 0) ? true : false;
}
bool Command::checkCountParams(char *params, CountParams count)
{
	int countArguments = 0;

	char *arg = new char[strlen(params) + 1];
	strcpy(arg, params);

	char *pch = strtok(arg, ",");

	for (countArguments = 0; pch != NULL; countArguments++) {
		pch = strtok(NULL, ",");
	}

	return (countArguments == count) ? true : false;
}