#pragma comment(lib, "wsock32.lib")

#include "headers\Headers.h"
#include <conio.h>

WSADATA ws;

int main()
{			
	WSAStartup(0x101, &ws); // Initialize the process of wsock32.dll library

	CommandLine *cmd = new CommandLine();
	Control *control = new Control();

	Commands command;
	bool exit = false;

	do {
		char *request = NULL;

		cmd->setCommandLine();
		request = cmd->getRequest();

		if (Command::haveAnyArgs(request)) {
			command = Command::getCommandByStroke(request, true);
			char *args = NULL;
			args = Command::getCommandLineArguments(request);

			control->setControlWithParams(command, args);

			free(args);
			exit = false;
		} 
		else {
			command = Command::getCommandByStroke(request, false);

			control->setControl(command);
			exit = true;
		}

		free(request);

	} while ((command != EXIT) || !exit);

	delete cmd, control;
	Sleep(1000);

	WSACleanup(); // Clear filled resources for WinSock
	
	return 0;
}