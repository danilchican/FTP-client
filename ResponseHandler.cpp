#include "headers\Headers.h"

using namespace std;

unsigned int ResponseHandler::getCodeResponse(const char *request)
{
	unsigned int code = 0;

	for (int i = 0; request[i] >= '0' && request[i] <= '9'; i++) {
		code = code * 10 + request[i] - '0';
	}

	return code;
}
void ResponseHandler::handler(int code)
{
	switch (code) {
	case 421:
		throw "Timeout... Connection lost";
		break;
	case 0:
		throw "Something wrong...";
		break;
	case 530:
		throw "Login is incorrect";
		break;
	default:
		break;
	}
}
