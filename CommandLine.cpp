#pragma comment(lib, "wsock32.lib")

#include <iostream>
#include <string>
#include <sstream>
#include <Winsock.h>
#include "headers\CommandLine.h"

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
	cout << this->cmd << endl;

}
const char * CommandLine::getRequest()
{
	return cmd;
}