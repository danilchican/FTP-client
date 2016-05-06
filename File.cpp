#include "headers\Headers.h"
#include <fstream>
using namespace std;

File::File(Connection *c1, Connection *c2, char *params) : bytes(0), path(NULL)
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

	while (pch != NULL) {
		if ((pch = strtok(NULL, " ")) != NULL) {
			int length = strlen(arguments) + strlen(pch) + 1;

			arguments = (char *)realloc(arguments, length + 1);
			strcat_s(arguments, length, pch);
		}
		else {
			break;
		}

		if ((pch = strtok(NULL, " ")) != NULL) {
			arguments = (char *)realloc(arguments, strlen(arguments) + 2);
			strcat_s(arguments, strlen(arguments) + 2, ",");
		}
	}

}
bool File::find(Commands com)
{
	try {
		char *command = new char[strlen(fileName) + 6];
		command[0] = '\0';

		switch (com)
		{
		case DOWNLOAD_FILE:
			strcat(command, "RETR ");
			strcat(command, fileName);
			break;
		case UPLOAD_FILE:
			strcat(command, "STOR ");
			strcat(command, fileName);
			break;
		}

		Command::sendCommand(c1->getSock(), "TYPE I");
		ResponseHandler::getCodeResponse(c1->ServerResponse());

		Command::sendCommand(c1->getSock(), command);

		c2->Connect();

		char *response = c1->ServerResponse();

		int code = ResponseHandler::getCodeResponse(response);
		ResponseHandler::handler(code);

		switch (com)
		{
		case DOWNLOAD_FILE:
			this->setFileSize(response, true);
			break;
		case UPLOAD_FILE:
			this->setPath();
			this->setFileSize(response, false);
			break;
		}

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
	try {
		if (!this->find(DOWNLOAD_FILE)) {
			return false;
		}
		else {
			this->setPath();

			if (!(this->downloadProcess())) {
				return false;
			}

			return true;
		}
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
		return false;
	}
}
bool File::upload()
{
	try	{
		if (!this->find(UPLOAD_FILE)) {
			return false;
		}
		else {
			if (!(this->uploadProcess())) {
				return false;
			}

			return true;
		}
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
		return false;
	}
}
bool File::_delete()
{
	try	{
		if (!(this->deleteProcess())) {
			return false;
		}

		return true;
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
		return false;
	}
}
bool File::rename()
{
	try	{
		if (!(this->renameProcess())) {
			return false;
		}

		return true;
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
		return false;
	}
}
void File::setPath()
{
	char *dirName = strtok(this->arguments, ",");

	int length = strlen(dirName) + strlen(this->fileName) + 2;
	this->path = new char[length];

	strcpy(this->path, dirName);
	strcat(this->path, "\\");
	strcat(this->path, this->fileName);
}
bool File::checkCountParams(char *params, CountParams count)
{
	int countArguments = 0;

	char *arg = new char[strlen(params) + 1];
	strcpy(arg, params);

	char *pch = strtok(arg, ",");

	for (countArguments = 0; pch != NULL; countArguments++) {
		pch = strtok(NULL, ",");
	}

	return (countArguments == count) ? true : false;
}
bool File::hasDirectory(char *params)
{
	if (!File::checkCountParams(params, TWO_PARAMS)) {
		cout << "You haven't all params to download.\nSee --help. dd [file] [path]" << endl;
		return false;
	}		

	char buff[255];
	strcpy(buff, params);

	char *dirName = strtok(buff, ",");
	
	for (int countArguments = 0; dirName != NULL && countArguments != 1; countArguments++) {
		dirName = strtok(NULL, ",");
	}
	
	DWORD ftyp = GetFileAttributesA(dirName);

	if (ftyp == INVALID_FILE_ATTRIBUTES) {
		cout << "Directory is not correct" << endl; 
		return false; 
	}

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
		return true;   
	}
}
bool File::hasFileInSystem(char *params)
{
	if (!File::checkCountParams(params, TWO_PARAMS)) {
		cout << "You haven't all params to download.\nSee --help. ud [file] [path]" << endl;
		return false;
	}

	char buff[255];
	strcpy(buff, params);

	char *fileName, *dirName;
	char *local = strtok(buff, ",");
	fileName = new char[strlen(local) + 1];
	strcpy(fileName, local);
	local = strtok(NULL, ",");
	dirName = new char[strlen(local) + 1];
	strcpy(dirName, local);

	char *result = new char[strlen(fileName) + strlen(dirName) + 3];
	strcpy(result, dirName);
	strcat(result, "\\");
	strcat(result, fileName);

	FILE * ptrFile = fopen(result, "r");

	if (ptrFile == NULL) {
		cout << "File doesn't exists" << endl;
		return false;
	}
	
	fclose(ptrFile);
	
	return true;
}
void File::setFileSize(char *res, bool is_download)
{
	if (is_download) {
		long long unsigned int size_in_bytes = 0;

		char *response = new char[strlen(res) + 1];
		strcpy(response, res);

		char* start = strchr(response, '(');
		char* end = strchr(response, ')');
		int num = end - start;

		char number[10000] = { '\0' };

		strncpy_s(number, start + 1, num - 1);

		char* token = strtok(number, " ");

		for (int i = 0; i < strlen(number); i++) {
			bytes = bytes * 10 + number[i] - '0';
		}
	} 
	else {
		LPDWORD w = 0;
		DWORD size_in_bytes = 0;
		HANDLE HFile;

		wchar_t *wtext = new wchar_t[strlen(this->path)];
		mbstowcs(wtext, this->path, strlen(this->path) + 1);
		LPWSTR ptr_file = wtext;

		HFile = CreateFile(ptr_file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		size_in_bytes = GetFileSize(HFile, NULL);

		this->bytes = size_in_bytes;
	}

}
bool File::downloadProcess()
{
	try {

		long  unsigned int no_of_bytes = 0;
		int cout_received_bytes = 0;
		char *text = new char[SIZE_BUFF + 1];

		char arr[21];
		memset(arr, ' ', 20);
		arr[20] = '\0';

		ofstream fout(this->path, ios_base::trunc);
		fout.close();

		long double cup = 0;
		int start = 0;
		
		for (int i = 0; (no_of_bytes = recv(c2->getSock(), text, SIZE_BUFF, 0)) > 0; ) {

			if (no_of_bytes == -1) {
				throw "Cannot connect to server...";
			}

			text[no_of_bytes] = '\0';

			ofstream fout(this->path, ios::binary | ios::app );
			fout.write(text, no_of_bytes);
			fout.close();
			
			cout_received_bytes += no_of_bytes;

			cup = 20 * cout_received_bytes / this->bytes;
			
			for (i = start; i <= cup; i++) {
				Sleep(50);
				fflush(stdin);
				
				if (i) {
					arr[i-1] = '#';
				}

				printf_s("[%s] %i%% (%i/%llu bytes)\r", arr, i * 5, cout_received_bytes, this->bytes);
			}		

			start = i;
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
bool File::uploadProcess()
{
	try	{
		DWORD read;
		HANDLE HFile;

		long  unsigned int no_of_bytes = 0;

		char arr[21];
		char *buffer = new char[SIZE_BUFF + 1];

		long double cup = 0;
		int start = 0;
		int cout_sended_bytes = 0;

		memset(arr, ' ', 20);
		arr[20] = '\0';

		wchar_t *wtext = new wchar_t[strlen(this->path)];
		mbstowcs(wtext, this->path, strlen(this->path) + 1);  
		LPWSTR ptr_file = wtext;

		HFile = CreateFile(ptr_file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		SetFilePointer(HFile, 0, NULL, FILE_BEGIN);

		for (int i = 0; ReadFile(HFile, buffer, SIZE_BUFF, &read, NULL) && (read > 0);)	{

			if (read == -1) {
				throw "Cannot connect to server...";
			}

			buffer[read] = '\0';

			send(c2->getSock(), buffer, read, 0);

			cout_sended_bytes += read;

			cup = 20 * cout_sended_bytes / this->bytes;

			for (i = start; i <= cup; i++)
			{
				Sleep(50);
				fflush(stdin);
				
				if (i) {
					arr[i - 1] = '#';
				}

				printf_s("[%s] %i%% (%i/%llu bytes)\r", arr, i * 5, cout_sended_bytes, this->bytes);
			}

			start = i;
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
bool File::deleteProcess()
{
	try {
		char *command = new char[strlen(fileName) + 6];
		command[0] = '\0';

		strcat(command, "DELE ");
		strcat(command, fileName);

		Command::sendCommand(c1->getSock(), command);

		char *response = c1->ServerResponse();

		int code = ResponseHandler::getCodeResponse(response);
		ResponseHandler::handler(code);

		return true;
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}

	return false;
}
bool File::renameProcess()
{
	try {
		char command[255],
			 fileTo[255],
			 *pch;

		command[0] = '\0';
		fileTo[0] = '\0';

		strcat(command, "RNFR ");
		strcat(command, fileName);
		
		Command::sendCommand(c1->getSock(), command);

		char *response = c1->ServerResponse();

		int code = ResponseHandler::getCodeResponse(response);
		ResponseHandler::handler(code);

		strcpy(fileTo, this->arguments);

		strcpy(command, "RNTO ");
		strcat(command, fileTo);

		Command::sendCommand(c1->getSock(), command);

		response = c1->ServerResponse();

		code = ResponseHandler::getCodeResponse(response);
		ResponseHandler::handler(code);

		return true;
	}
	catch (char *message)
	{
		cout << "Handler: " << message << endl;
	}

	return false;
}
