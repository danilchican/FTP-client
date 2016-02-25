#include "headers\Headers.h"

// host: vh60.hoster.by
// port: 21

int main()
{
	WSAStartup(0x101, &ws); // Initialize the process of wsock32.dll library
	
	CommandLine *cmd = new CommandLine;
	Control *control = new Control;

	do
	{
		cmd->setCommandLine();
		control->setControl(cmd->getRequest());

	} while (true);

		
	WSACleanup(); // Clear filled resources for WinSock

	return 0;
}