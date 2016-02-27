#include "headers\Headers.h"

using namespace std;

unsigned int ResponseHandler::getCodeResponse(const char *request)
{
	unsigned int code = 0;
	// char code_response[4];

	for (int i = 0; request[i] >= '0' && request[i] <= '9' ;i++)
		code = code*10 + request[i] - '0';

	return code;
}
void ResponseHandler::handler(int code)
{
	switch (code)
	{
	case 530:
		throw "Login is not correct";
		break;
	default:
		break;
	}
}