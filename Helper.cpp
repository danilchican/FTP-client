#include "headers\Headers.h"
#include <iomanip>

using namespace std;

void Helper::commands()
{
	char commands[COUNT_COMMANDS][2][80] =
	{
		{ "create [host_id]", "Create connection to your host" },
		{ "close", "Destroy created session" },
		{ "mkdir [name]", "Create new directory" },
		{ "rmdir [name]", "Deletes the named directory on the remote host" },
		{ "rm [file]", "Deletes the named file on the remote host" },
		{ "rn [from] [to]", "Rename the file on the remote host" },
		{ "pwd", "Return current directory" },
		{ "hosts", "Display list of hosts stored in database" },
		{ "addhost [host] [port] [user] [pass]", "Add new host to the DB" },
		{ "rmhost [id]", "Delete host from the database" },
		{ "download [file] [path]", "Download the file from the remote host" },
		{ "upload [file] [path]", "Upload the file from client to the remote host" },
		{ "cd [path]", "Change current directory" },
		{ "up", "Moves up to the parent directory" },
		{ "ls", "Display the contents of a current directory" },
		{ "help", "Display available commands" },
		{ "clear", "Clear console screen" },
		{ "exit", "Exit from programm" }
	};

	cout << "Commands: " << endl;

	for (int i = 0; i < COUNT_COMMANDS - 1; i++) { // display commands and description
		cout << "   " << setw(35) << left << commands[i][0] << "   " << commands[i][1] << endl;
	}
}