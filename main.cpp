#pragma comment(lib, "wsock32.lib")

#include "headers\Headers.h"

WSADATA ws;

// host: vh60.hoster.by, port: 21

int main()
{
	WSAStartup(0x101, &ws); // Initialize the process of wsock32.dll library

	/////////////////////////////////////////////////////
	char arr[51], i;
	memset(arr, ' ', 50);
	arr[50] = '\0';
	for (i = 0; i <= 50; i++)                               // progress bar
	{
		printf_s("[%s] %i%%\r", arr, i * 2);
		fflush(stdout);
		arr[i] = '#'; 
		Sleep(50);
	}
	std::cout << std::endl;
	/////////////////////////////////////////////////////


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