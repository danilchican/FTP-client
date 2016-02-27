#include "headers\Headers.h"
using namespace std;

void Control::setControl(Commands command)
{
	switch (command)
	{
	case CONNECT:
		if (c1 == NULL)
		{
			c1 = new Connection(); // Create new connection without params

			if (!c1->Connect()) // Connect to host by socket 
			{
				cout << "Cannot connect to host" << endl;
				delete c1;
				c1 = NULL;
			}
			else
			{
				cout << "Connected to host\nStarting authorisation..." << endl;
				if (!c1->Authorisation())
				{
					cout << "Cannot connect to host." << endl;
					delete c1;
					c1 = NULL;
				}
				else
				{
					cout << "User " << c1->user() << " logged in" << endl; // to complete
					c1->SetPassiveMode();
					c2 = new Connection(c1->IPHost(), c1->activePort());
				}	
			}
		}
		break;
	case DISCONNECT:
		if (c1 != NULL)
		{
			cout << "Disconnection..." << endl;
			c1->Close(); // Close connection
			delete c1, c2;
			c1 = NULL;
			c2 = NULL;
		}
		else
			cout << "Connection already closed." << endl;
		break;
	case CURRENT_DIR:
		Directory::currentDirectory(c1);
		break;
	case MAKE_DIR:
		Directory::makeDirectory(c1);
		break;
	case CLEAR_CONSOLE:
		system("cls");
		break;
	case COMMAND_ERROR:
		cout << "Command not found" << endl;
		break;
	case EXIT:
		if (c1 != NULL)
		{
			c1->Close(); // Close connection
			delete c1, c2;
			c1 = NULL; c2 = NULL;
			cout << "Clear filled resources..." << endl;
		}
		cout << "Closing console..." << endl;
		break;
	default:
		break;
	}
}