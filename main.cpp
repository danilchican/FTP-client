#pragma comment(lib, "wsock32.lib")

#include "headers\Headers.h"

WSADATA ws;

// host: vh60.hoster.by, port: 21

int main()
{
	WSAStartup(0x101, &ws); // Initialize the process of wsock32.dll library
	
	CommandLine *cmd = new CommandLine;
	Control *control = new Control();

	do
	{
		cmd->setCommandLine();
		control->setControl(Command::getCommandByStroke(cmd->getRequest()));
	} while (Command::getCommandByStroke(cmd->getRequest()) != EXIT);

	WSACleanup(); // Clear filled resources for WinSock

	return 0;
}