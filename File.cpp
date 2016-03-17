#include "headers\Headers.h"
#include <fstream>
using namespace std;

File::File(Connection *c1, Connection *c2, char *params) : bytes(0)
{
	char *commandLine = new char[strlen(params) + 1];
	strcpy_s(commandLine, strlen(params) + 1, params);

	this->c1 = c1;
	this->c2 = c2;

	char *pch = strtok(commandLine, ",");

	this->fileName = new char[strlen(pch) + 1];
	strcpy_s(this->fileName, strlen(pch) + 1, pch);

	this->arguments = new char[2];
	arguments[0] = '\0';

	while (pch != NULL)
	{
		if ((pch = strtok(NULL, " ")) != NULL)
		{
			int length = strlen(arguments) + strlen(pch) + 1;

			arguments = (char *)realloc(arguments, length + 1);
			strcat_s(arguments, length, pch);
		}
		else
			break;

		if ((pch = strtok(NULL, " ")) != NULL)
		{
			arguments = (char *)realloc(arguments, strlen(arguments) + 2);
			strcat_s(arguments, strlen(arguments) + 2, ",");
		}
	}

}
bool File::find()
{
	try 
	{
		char *command = new char[strlen(fileName) + 6];
		command[0] = '\0';

		strcat(command, "RETR ");
		strcat(command, fileName);

		Command::sendCommand(c1->getSock(), "TYPE I");
		ResponseHandler::getCodeResponse(c1->ServerResponse());


		Command::sendCommand(c1->getSock(), command);

		c2->Connect();

		char *response = c1->ServerResponse();

		int code = ResponseHandler::getCodeResponse(response);
		ResponseHandler::handler(code);

		this->setFileSize(response);

		return true;
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}

	return false;
}
bool File::download()
{
	try
	{
		if (!this->find())
			return false;
		else
		{
			if (!(this->downloadProcess()))
				return false;

			return true;
		}
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
		return false;
	}
	
}
void File::setFileSize(char *res)
{
	long long unsigned int size_in_bytes = 0;

	char *response = new char[strlen(res) + 1];
	strcpy(response, res);

	char* start = strchr(response, '(');
	char* end = strchr(response, ')');
	int num = end - start;

	char number[10000] = { '\0' };

	strncpy_s(number, start + 1, num - 1);

	char* token = strtok(number, " ");

	for (int i = 0; i < strlen(number); i++)
		bytes = bytes * 10 + number[i] - '0';
}
bool File::downloadProcess()
{
	try
	{
		long  unsigned int no_of_bytes = 0;
		int cout_received_bytes = 0;
		char *text = new char[SIZE_BUFF + 1];

		char arr[51], i;
		memset(arr, ' ', 50);
		arr[50] = '\0';

		long double cup = 0;
		
		for (int i = 0; (no_of_bytes = recv(c2->getSock(), text, SIZE_BUFF, 0)) > 0; )
		{
			if (no_of_bytes == -1)
				throw "Cannot connect to server...";

			text[no_of_bytes] = '\0';

			ofstream fout(this->fileName, ios::binary | ios::app );
			fout.write(text, no_of_bytes);
			fout.close();
			
			cout_received_bytes += no_of_bytes;

			cup = 50 * cout_received_bytes / this->bytes;
			for (i = 0; i <= cup; i++)
			{
				arr[i] = '#';
				printf_s("[%s] %i%% (%i/%llu bytes)\r", arr, i * 2, cout_received_bytes, this->bytes);
			}		
		}
		cout << endl;
		c2->CloseSocket();

		int code = ResponseHandler::getCodeResponse(c1->ServerResponse());
		ResponseHandler::handler(code);

		return true;
	}
	catch (char *message)
	{
		cout << "\nHandler: " << message << endl;
	}

	return false;
}