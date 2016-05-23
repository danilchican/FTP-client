#include "headers\Headers.h"

using namespace std;

void Directory::makeDirectory(Connection *c1, char *path)
{
	try {
		char *command = new char[strlen(path) + 5];
	
		strcpy_s(command, 5, "MKD ");
		strcat_s(command, strlen(command) + strlen(path) + 1, path);

		Command::sendCommand(c1->getSock(), command);
		int code = ResponseHandler::getCodeResponse(c1->serverResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}	
}
void Directory::currentDirectory(Connection *c1)
{
	Command::sendCommand(c1->getSock(), "PWD");

	char cdir[255];

	strcpy_s(cdir, 255, Directory::processingCurrentDirectory(c1->serverResponse()));

	cout << "Current directory: " << "\"" << cdir << "\"" << endl;	
}
char * Directory::processingCurrentDirectory(char *resp)
{
	char current[255];

	bool got_in = false,
		got_out = false;

	int start = 0, end = 0, 
		length = strlen(resp);
	
	for (int i = 0; i < length && !got_in; i++) {

		if (resp[i] == '"')	{
			got_in = true;
			start = i + 1;

			for (int j = i + 1; j < length && !got_out; j++) {
				if (resp[j] == '"')	{
					got_out = true;
					end = j;
				}
			}
		}
	}

	int i = 0;

	for (i = 0; i < end - start; i++) {
		current[i] = resp[start + i];
	}
		
	current[i] = '\0';

	return current;
}
void Directory::changeDirectory(Connection *c1, char *path)
{
	try	{
		char *command = new char[strlen(path) + 5];

		strcpy_s(command, 5, "CWD ");
		strcat_s(command, strlen(command) + strlen(path) + 1, path);

		Command::sendCommand(c1->getSock(), command);
		int code = ResponseHandler::getCodeResponse(c1->serverResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}
}
void Directory::removeDirectory(Connection *c1, char *path)
{
	try	{
		char *command = new char[strlen(path) + 5];

		strcpy_s(command, 5, "RMD ");
		strcat_s(command, strlen(command) + strlen(path) + 1, path);

		Command::sendCommand(c1->getSock(), command);
		int code = ResponseHandler::getCodeResponse(c1->serverResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}
}
void Directory::moveUp(Connection *c1)
{
	try	{
		Command::sendCommand(c1->getSock(), "CDUP");

		int code = ResponseHandler::getCodeResponse(c1->serverResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}
}
void Directory::list(Connection *c1, Connection *c2)
{
	try	{
		Command::sendCommand(c1->getSock(), "LIST");
		
		int code = ResponseHandler::getCodeResponse(c1->serverResponse());
		ResponseHandler::handler(code);

		char *text = new char[SIZE_BUFF + 1];
		text[0] = '\0';

		int no_of_bytes;

		while ((no_of_bytes = recv(c2->getSock(), text, SIZE_BUFF, 0)) > 0)	{

			if (no_of_bytes == -1) {
				throw "Connection lost...";
			}
			
			text[no_of_bytes] = '\0';
			cout << text;
			fflush(stdout);
		}
		cout << endl;

		c2->closeSocket();

		code = ResponseHandler::getCodeResponse(c1->serverResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}
}