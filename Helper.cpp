#include "headers\Headers.h"
#include <iomanip>

using namespace std;

void Helper::Commands()
{
	char commands[COUNT_COMMANDS][2][80] =
	{
		{ "connect", "Create connection to your host" },
		{ "reconnect", "Connect to exists host" },
		{ "disconnect", "Destroy created session" },
		{ "mkdir", "Create new directory" },
		{ "rmdir", "Deletes the named directory on the remote host" },
		{ "cdir", "Return current directory" },
		{ "dd", "Download the file from the remote host" },
		{ "cd", "Change current directory" },
		{ "up", "Moves up to the parent directory" },
		{ "ls", "Diplay the contents of a current directory" },
		{ "help", "Display available commands" },
		{ "status", "Returns general status information about the FTP server process" },
		{ "clear", "Clear console screen" },
		{ "exit", "Exit from programm" }
	};

	cout << "Commands: " << endl;

	for (int i = 0; i < COUNT_COMMANDS; i++) // display commands and description
		cout << "   " << setw(15) << left << commands[i][0] << "   " << commands[i][1] << endl; 
}