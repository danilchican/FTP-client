#include "headers\Headers.h"

using namespace std;

unsigned int ResponseHandler::getCodeResponse(const char *request)
{
	unsigned int code = 0;

	for (int i = 0; request[i] >= '0' && request[i] <= '9' ;i++)
		code = code*10 + request[i] - '0';

	return code;
}
void ResponseHandler::handler(int code)
{
	switch (code)
	{
	case 421:
		throw "Timeout... Connection lost";
		break;
	case 0:
		throw "Something wrong...";
		break;
	case 530:
		throw "Login is incorrect";
		break;
	case 550:
		throw "No such file or directory";
		break;
	default:
		break;
	}
}
char * ResponseHandler::processingCurrentDirectory(char *response)
{
	// Lets extract the string '"/" Current directory'

	char cdir[255] = { '\0' };
	bool got_in = false,
		 got_out = false;
	int start = 0, end = 0;

	int length = strlen(response);

	for (int i = 0; i < length && !got_in; i++)
	{
		if (response[i] == '"')
		{
			got_in = true;
			start = i + 1;
			for (int j = i + 1; j < length && !got_out; j++)
			{
				if (response[j] == '"')
				{
					got_out = true;
					end = j;
				}
			}
		}
	}

	for (int i = 0; i < end - start; i++)
		cdir[i] = response[start + i];

	return cdir;
}