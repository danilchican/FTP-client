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
					cout << "User " << c1->user() << " logged in" << endl;
					c1->SetPassiveMode();
				}	
			}
		}
		break;
	case DISCONNECT:
		if (c1 != NULL)
		{
			c1->Close(); // Close connection
			delete c1;
			c1 = NULL;
		}
		else
			cout << "Connection already closed." << endl;
		break;
	case CLEAR_CONSOLE:
		system("cls");
		break;
	case COMMAND_ERROR:
		cout << "Command not found" << endl;
		break;
	default:

		break;
	}

	
	
}