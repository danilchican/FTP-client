#include "headers\Headers.h"
#include <string>

using namespace std;

void CommandLine::setCommandLine()
{
	cout << "> ";
	this->setData();
}
void CommandLine::setData()
{
	string cmdLine;
	fflush(stdin);
	getline(cin, cmdLine);
	this->cmd = new char[cmdLine.length() + 1];
	strcpy_s(this->cmd, cmdLine.length() + 1, cmdLine.c_str());
}
char * CommandLine::getRequest()
{
	return cmd;
}
