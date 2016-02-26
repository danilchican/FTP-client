#include "headers\Headers.h"
using namespace std;

void Control::setControl(Commands command)
{
	Connection *c1 = NULL;

	switch (command)
	{
	case CONNECT:
		if (c1 == NULL)
		{
			c1 = new Connection(); // Create new connection without params

			if (!c1->Connect()) // Connect to host by socket 
				cout << "Cannot connect to host." << endl;
			else
			{
				cout << "Connected to host...\nStarting authorisation..." << endl;
				if (!c1->Authorisation())
					cout << "Cannot connect to host." << endl;
				else
					cout << "" << endl;
			}	

		}
		break;
	case DISCONNECT:
		if (c1 != NULL)
			c1->Close(); // Close connection
		else
			cout << "Connection already closed." << endl;
		break;
	default:
		break;
	}

	
	
}