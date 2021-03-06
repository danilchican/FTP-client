#include "headers\Headers.h"
using namespace std;

void Control::setControl(Commands command)
{
	switch (command) {
	case CONNECT:
		cout << "You haven't all params to connect to host.\nSee --help. create [host_id]" << endl;
		break;
	case DISCONNECT:
		if (c1 != NULL) {
			cout << "Disconnection..." << endl;
			c1->close(); // Close connection
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
			cout << "You haven't all params to add new host.\nSee --help. addhost [host] [port] [user] [pass]" << endl;
		break;
	case DELETE_HOST:
		cout << "You haven't all params to delete host.\nSee --help. rmhost [id]" << endl;
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
			if (c1->setPassiveMode()) {
				c2 = new Connection(c1->getIPHost(), c1->activePort());
				c2->connectToServer();
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
		Helper::commands();
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
			c1->close(); // Close connection
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
		if (c1 == NULL) {
			if (!Command::checkCountParams(params, ONE_PARAM)) {
				cout << "You haven't all params to connect to host.\nSee --help. create [host_id]" << endl;
			}
			else {
				Database * db = new Database(params, true);
				if (db->hasHost()) {
					c1 = new Connection(db); // Create new connection without params

					cout << "Starting connection..." << endl;
					if (!c1->connectToServer()) { // Connect to host by socket 
						cout << "Cannot connect to host" << endl;

						delete c1;
						c1 = NULL;
					}
					else {
						cout << "Connected to host\nStarting authorisation..." << endl;
						if (!c1->authorisation()) {
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
					cout << "Can't find host by id = " << params << "..." << endl;
				}
			}		
		}
		else {
			cout << "You have already connection" << endl;
		}
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
			if (!Command::checkCountParams(params, FOUR_PARAMS)) {
				cout << "You haven't all params to add new host.\nSee --help. addhost [host] [port] [user] [pass]" << endl;
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
	case DELETE_HOST:
		if (!Command::checkCountParams(params, ONE_PARAM)) {
			cout << "You haven't all params to delete host.\nSee --help. rmhost [id]" << endl;
		}
		else {
			Database db;
			int host_id = atoi(params);

			if (!db.deleteHost(host_id)) {
				cout << "Cannot delete host from DB..." << endl;
			}
			else {
				cout << "Host with id = " << host_id << " successfully deleted!" << endl;
			}
		}
		break;
	case MAKE_DIR:
		if (c1 != NULL)	{
			if (!Command::checkCountParams(params, ONE_PARAM)) {
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
			if (!Command::checkCountParams(params, ONE_PARAM)) {
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
				if (c1->setPassiveMode()) {
					c2 = new Connection(c1->getIPHost(), c1->activePort());
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

					c2->closeSocket();

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
				if (c1->setPassiveMode()) {
					c2 = new Connection(c1->getIPHost(), c1->activePort());
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

					c2->closeSocket();

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
			if (!Command::checkCountParams(params, ONE_PARAM)) {
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
			if (!Command::checkCountParams(params, TWO_PARAMS)) {
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
			if (!Command::checkCountParams(params, ONE_PARAM)) {
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
