#pragma comment(lib, "wsock32.lib")

#include "headers\Headers.h"

WSADATA ws;

// host: vh60.hoster.by, port: 21

int main()
{
	WSAStartup(0x101, &ws); // Initialize the process of wsock32.dll library
	
	CommandLine *cmd = new CommandLine();
	Control *control = new Control();
	bool exit = false;
	do
	{
		cmd->setCommandLine();

		if (control->haveAny(cmd->getRequest()))
		{
			control->setControlWithParams(Command::getCommandByStroke(cmd->getRequest(), true),
				Command::getCommandLineArguments(cmd->getRequest()));

			exit = false;
		}
		else
		{
			control->setControl(Command::getCommandByStroke(cmd->getRequest(), false));
			exit = true;
		}			
	} while ((Command::getCommandByStroke(cmd->getRequest(), false) != EXIT) || !exit);

	delete cmd, control;
	Sleep(2000);

	WSACleanup(); // Clear filled resources for WinSock

	return 0;
}