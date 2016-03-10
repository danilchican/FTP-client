#include "headers\Headers.h"
#include <iomanip>

using namespace std;

void Helper::Commands()
{
	char commands[COUNT_COMMANDS][2][80] =
	{
		{ "connect", "Create connection to your host" },
		{ "disconnect", "Destroy created session" },
		{ "mkdir", "Create new directory" },
		{ "chdir", "Change current directory" },
		{ "cdir", "Return current directory" },
		{ "help", "Display available commands" },
		{ "clear", "Clear console screen" },
		{ "exit", "Exit from programm" }
	};

	cout << "Commands: " << endl;

	for (int i = 0; i < COUNT_COMMANDS; i++) // display commands and description
		cout << "   " << setw(15) << left << commands[i][0] << "   " << commands[i][1] << endl; 
}