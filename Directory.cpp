#include "headers\Headers.h"

using namespace std;

void Directory::makeDirectory(Connection *c1, char *path)
{
	try
	{
		char *command = new char[strlen(path) + 5];
	
		strcpy_s(command, 5, "MKD ");
		strcat_s(command, strlen(command) + strlen(path) + 1, path);

		Command::sendCommand(c1->getSock(), command);
		int code = ResponseHandler::getCodeResponse(c1->ServerResponse());
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
	strcpy_s(cdir, 255, ResponseHandler::processingCurrentDirectory(c1->ServerResponse()));
	
	cout << "Current directory: " << "\""<< cdir << "\"" << endl;
}
void Directory::changeDirectory(Connection *c1, char *path)
{
	try
	{
		char *command = new char[strlen(path) + 5];

		strcpy_s(command, 5, "CWD ");
		strcat_s(command, strlen(command) + strlen(path) + 1, path);

		Command::sendCommand(c1->getSock(), command);
		int code = ResponseHandler::getCodeResponse(c1->ServerResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}
}
void Directory::removeDirectory(Connection *c1, char *path)
{
	try
	{
		char *command = new char[strlen(path) + 5];

		strcpy_s(command, 5, "RMD ");
		strcat_s(command, strlen(command) + strlen(path) + 1, path);

		Command::sendCommand(c1->getSock(), command);
		int code = ResponseHandler::getCodeResponse(c1->ServerResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}
}
void Directory::moveUp(Connection *c1)
{
	try
	{
		Command::sendCommand(c1->getSock(), "CDUP");

		int code = ResponseHandler::getCodeResponse(c1->ServerResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}
}
void Directory::list(Connection *c1, Connection *c2)
{
	try
	{
		Command::sendCommand(c1->getSock(), "LIST");
		
		int code = ResponseHandler::getCodeResponse(c1->ServerResponse());
		ResponseHandler::handler(code);

		char text[SIZE_BUFF] = { '/0' };

		int no_of_bytes;

		while ((no_of_bytes = recv(c2->getSock(), text, SIZE_BUFF, 0)) > 0)
		{
			text[no_of_bytes - 1] = '\0';
			cout << text;
			fflush(stdout);
		}
		cout << endl;

		c2->CloseSocket();

		code = ResponseHandler::getCodeResponse(c1->ServerResponse());
		ResponseHandler::handler(code);
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}
}
bool Directory::checkoutMakeDirParams(char *params)
{
	int countArguments = 0;

	int length = strlen(params) + 1;
	char *arg = new char[length];
	strcpy_s(arg, length, params);

	char *pch = strtok(arg, " ,");

	for (countArguments = 0; pch != NULL; countArguments++)
		pch = strtok(NULL, ",");

	if (countArguments == 1)
		return true;
	else
		return false;
}