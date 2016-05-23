#include "headers\Headers.h"

bool Checkout::checkCountParams(char *params, CountParams count)
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