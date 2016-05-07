#include "headers\Headers.h"
using namespace std;

void Control::setControl(Commands command)
{
	switch (command) {
	case CONNECT:
		if (c1 == NULL) {
			c1 = new Connection(); // Create new connection without params

			if (!c1->Connect()) { // Connect to host by socket 
				cout << "Cannot connect to host" << endl;
				delete c1;
				c1 = NULL;
			} 
			else {
				cout << "Connected to host\nStarting authorisation..." << endl;
				if (!c1->Authorisation()) {
					cout << "Cannot connect to host." << endl;
					delete c1;
					c1 = NULL;
				} 
				else {
					cout << "User " << c1->user() << " logged in" << endl; // to complete
				}
			}
		}
		else {
			cout << "You have already connection" << endl;
		}	
		break;
	case DISCONNECT:
		if (c1 != NULL) {
			cout << "Disconnection..." << endl;
			c1->Close(); // Close connection
			delete c1, c2;
			c1 = NULL;
			c2 = NULL;
		}
		else {
			cout << "Connection already closed." << endl;
		}
		break;
	case HOSTS: 
		{
			Database db;
			db.getHostsList();
		}
		break;
	case ADD_HOST:
			cout << "You haven't all params to add new host.\nSee --help. addhost [host] [user] [pass]" << endl;
		break;
	case CURRENT_DIR:
		if (c1 != NULL) {
			Directory::currentDirectory(c1);
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case DOWNLOAD_FILE:
		if (c1 != NULL) {
			cout << "You haven't all params to download.\nSee --help. download [file] [path]" << endl;
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case UPLOAD_FILE:
		if (c1 != NULL) {
			cout << "You haven't all params to uploading file.\nSee --help. upload [file] [path]" << endl;
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case DELETE_FILE:
		if (c1 != NULL) {
			cout << "You haven't all params to delete file.\nSee --help. rm [file]" << endl;
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case RENAME_FILE:
		if (c1 != NULL) {
			cout << "You haven't all params to rename file.\nSee --help. rn [from] [to]" << endl;
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case LIST:
		if (c1 != NULL)	{
			if (c1->SetPassiveMode()) {
				c2 = new Connection(c1->IPHost(), c1->activePort());
				c2->Connect();
				Directory::list(c1, c2);

				delete c2;
			}
			else {
				cout << "Cannot connect to server..." << endl;
			}
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case MAKE_DIR:
		if (c1 != NULL) {
			cout << ONLY_ONE_PARAM << endl;
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;

	case CHANGE_DIR:
		if (c1 != NULL) {
			cout << ONLY_ONE_PARAM << endl;
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case DELETE_DIR:
		if (c1 != NULL) {
			cout << ONLY_ONE_PARAM << endl;
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case HELP:
		Helper::Commands();
		break;
	case MOVE_UP:
		if (c1 != NULL) {
			Directory::moveUp(c1);
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case CLEAR_CONSOLE:
		system("cls");
		break;
	case COMMAND_ERROR:
		cout << "Command not found" << endl;
		break;
	case EXIT:
		if (c1 != NULL)	{
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
	switch (command) {
	case CONNECT:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case DISCONNECT:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case CURRENT_DIR:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case HOSTS:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case ADD_HOST:
			if (!Checkout<bool>::checkCountParams(params, THREE_PARAMS)) {
				cout << "You haven't all params to add new host.\nSee --help. addhost [host] [user] [pass]" << endl;
			}
			else {
				Database *db = NULL;

				db = new Database(params);

				if (!db->addNewHost()) {
					cout << "Cannot add new host to the DB..." << endl;
				}
				else {
					cout << "New host successfully added!" << endl;
				}
				
				delete db;
			}
		break;
	case MAKE_DIR:
		if (c1 != NULL)	{
			if (!Directory::checkoutMakeDirParams(params)) {
				cout << ONLY_ONE_PARAM << endl;
			}
			else {
				Directory::makeDirectory(c1, params);
			}
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case CHANGE_DIR:
		if (c1 != NULL) {
			if (!Directory::checkoutMakeDirParams(params)) {
				cout << ONLY_ONE_PARAM << endl;
			}
			else {
				Directory::changeDirectory(c1, params);
			}
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case MOVE_UP:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case LIST:
		cout << PARAMS_NOT_REQUIRED << endl;
		break;
	case DOWNLOAD_FILE:
		if (c1 != NULL)	{
			if (File::hasDirectory(params))	{
				if (c1->SetPassiveMode()) {
					c2 = new Connection(c1->IPHost(), c1->activePort());
					File *file = NULL;

					try {
						file = new File(c1, c2, params);

						if (!file->download()) {
							cout << "Cannot download file..." << endl;
						}
					}
					catch (char *message)
					{
						cout << "Handler: " << message << endl;
					}

					c2->CloseSocket();

					delete c2, file;
				}
				else {
					cout << "Reconnect to server, please." << endl;
				}
			}				
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case UPLOAD_FILE:
		if (c1 != NULL)	{
			if (File::hasFileInSystem(params)) {
				if (c1->SetPassiveMode()) {
					c2 = new Connection(c1->IPHost(), c1->activePort());
					File *file = NULL;

					try	{
						file = new File(c1, c2, params);

						if (!file->upload()) {
							cout << "Cannot download file..." << endl;
						}
					}
					catch (char *message)
					{
						cout << "Handler: " << message << endl;
					}

					c2->CloseSocket();

					delete c2, file;
				}
				else {
					cout << "Reconnect to server, please." << endl;
				}
			}
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case DELETE_FILE:
		if (c1 != NULL)	{
			if (!File::checkCountParams(params, ONE_PARAM)) {
				cout << "You haven't all params to delete file.\nSee --help. rm [file]" << endl;
			}
			else {
				File *file = NULL;

				try {
					file = new File(c1, c2, params);

					if (!file->_delete()) {
						cout << "Cannot delete file..." << endl;
					}
				}
				catch (char *message)
				{
					cout << "Handler: " << message << endl;
				}

				delete file;
			}
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case RENAME_FILE:
		if (c1 != NULL)	{
			if (!File::checkCountParams(params, TWO_PARAMS)) {
				cout << "You haven't all params to rename file.\nSee --help. rn [from] [to]"  << endl;
			}
			else {
				File *file = NULL;

				try {
					file = new File(c1, c2, params);

					if (!file->rename()) {
						cout << "Cannot rename file..." << endl;
					}
				}
				catch (char *message)
				{
					cout << "Handler: " << message << endl;
				}

				delete file;
			}
		}
		else {
			cout << "Does not have any connection." << endl;
		}
		break;
	case DELETE_DIR:
		if (c1 != NULL) {
			if (!Directory::checkoutMakeDirParams(params)) {
				cout << ONLY_ONE_PARAM << endl;
			}
			else {
				Directory::removeDirectory(c1, params);
			}
		}
		else {
			cout << "Does not have any connection." << endl;
		}
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

	for (countArguments = -1; pch != NULL; countArguments++) {
		pch = strtok(NULL, " -");
	}
	
	return (countArguments > 0) ? true : false;
}