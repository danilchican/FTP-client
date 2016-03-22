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
					cout << "User " << c1->user() << " logged in" << endl; // to complete
			}
		}
		else
			cout << "You have already connection" << endl;
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
		if (c1 != NULL)
			Directory::currentDirectory(c1);
		else
			cout << "Does not have any connection." << endl;
		break;
	case DOWNLOAD_FILE:
		if (c1 != NULL)
			cout << "You haven't all params to download.\nSee --help. dd [file] [path]" << endl;
		else
			cout << "Does not have any connection." << endl;
		break;
	case LIST:
		if (c1 != NULL)
		{
			if (c1->SetPassiveMode())
			{
				c2 = new Connection(c1->IPHost(), c1->activePort());
				c2->Connect();
				Directory::list(c1, c2);

				delete c2;
			}
			else
				cout << "Cannot connect to server..." << endl;
		}
		else
			cout << "Does not have any connection." << endl;
		break;
	case MAKE_DIR:
		if (c1 != NULL)
			cout << ONLY_ONE_PARAM << endl;
		else
			cout << "Does not have any connection." << endl;
		break;
	case RECONNECT:
		if (c1 != NULL)
			c1->Reconnect();
		else
			cout << "Does not have any connection." << endl;
		break;
	case CHANGE_DIR:
		if (c1 != NULL)
			cout << ONLY_ONE_PARAM << endl;
		else
			cout << "Does not have any connection." << endl;
		break;
	case DELETE_DIR:
		if (c1 != NULL)
			cout << ONLY_ONE_PARAM << endl;
		else
			cout << "Does not have any connection." << endl;
		break;
	case HELP:
		Helper::Commands();
		break;
	case MOVE_UP:
		if (c1 != NULL)
			Directory::moveUp(c1);
		else
			cout << "Does not have any connection." << endl;
		break;
	case STATUS:
		if (c1 != NULL)
			c1->status();
		else
			cout << "Does not have any connection." << endl;
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
void Control::setControlWithParams(Commands command, char *params)
{
	//cout << "Good it works. Params: " << endl;
	//cout << params << endl;

	switch (command)
	{
	case CONNECT:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case DISCONNECT:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case CURRENT_DIR:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case MAKE_DIR:
		if (c1 != NULL)
		{
			if (!Directory::checkoutMakeDirParams(params))
				cout << ONLY_ONE_PARAM << endl;
			else
				Directory::makeDirectory(c1, params);
		}
		else
			cout << "Does not have any connection." << endl;
		break;
	case CHANGE_DIR:
		if (c1 != NULL)
		{
			if (!Directory::checkoutMakeDirParams(params))
				cout << ONLY_ONE_PARAM << endl;
			else
				Directory::changeDirectory(c1, params);
		}
		else
			cout << "Does not have any connection." << endl;
		break;
	case MOVE_UP:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case LIST:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case RECONNECT:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case STATUS:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case DOWNLOAD_FILE:
		if (c1 != NULL)
		{
			if (File::hasDirectory(params))
			{
				if (c1->SetPassiveMode())
				{
					c2 = new Connection(c1->IPHost(), c1->activePort());
					File *file = NULL;
					try
					{
						file = new File(c1, c2, params);

						if (!file->download())
							cout << "Cannot download file..." << endl;
					}
					catch (char *message)
					{
						cout << "Handler: " << message << endl;
					}

					c2->CloseSocket();

					delete c2, file;
				}
				else
					cout << "Reconnect to server, please." << endl;
			}				
		}
		else
			cout << "Does not have any connection." << endl;
		break;
	case DELETE_DIR:
		if (c1 != NULL)
		{
			if (!Directory::checkoutMakeDirParams(params))
				cout << ONLY_ONE_PARAM << endl;
			else
				Directory::removeDirectory(c1, params);
		}
		else
			cout << "Does not have any connection." << endl;
		break;
	case COMMAND_ERROR:
		cout << "Command not found" << endl;
		break;
	case CLEAR_CONSOLE:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case HELP:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case EXIT:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	default:
		break;
	}
}
bool Control::haveAny(char *cmd)
{
	int countArguments;

	char *commandLine = new char[strlen(cmd) + 1];
	strcpy_s(commandLine, strlen(cmd) + 1, cmd);

	char *pch = strtok(commandLine, " -");

	for (countArguments = -1; pch != NULL; countArguments++)
		pch = strtok(NULL, " -");
	
	return (countArguments > 0) ? true : false;
}