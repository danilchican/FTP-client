#include "headers\Headers.h"

using namespace std;

void Directory::makeDirectory(Connection *c1)
{
	Command::sendCommand(c1->getSock(), "MKD public_html/newCat");
	c1->ServerResponse();
}
void Directory::currentDirectory(Connection *c1)
{
	Command::sendCommand(c1->getSock(), "PWD");

	char cdir[255];
	strcpy_s(cdir, 255, ResponseHandler::processingCurrentDirectory(c1->ServerResponse()));
	
	cout << "Current directory: " << "\""<< cdir << "\"" << endl;
}