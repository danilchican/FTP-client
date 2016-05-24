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
		cmd->setCommandLine();

		if (Command::haveAnyArgs(cmd->getRequest())) {
			command = Command::getCommandByStroke(cmd->getRequest(), true);
			char *args = Command::getCommandLineArguments(cmd->getRequest());

			control->setControlWithParams(command, args);

			free(args);
			exit = false;
		} 
		else {
			command = Command::getCommandByStroke(cmd->getRequest(), false);

			control->setControl(command);
			exit = true;
		}

	} while ((command != EXIT) || !exit);

	delete cmd, control;
	Sleep(1000);

	WSACleanup(); // Clear filled resources for WinSock
	
	return 0;
}