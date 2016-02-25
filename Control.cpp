#include <iostream>
#include <cstring>
using namespace std;

#include "headers\Connection.h"
#include "headers\Command.h"
#include "headers\Control.h"

void Control::setControl(const char *command)
{
	Connection *c1 = NULL;

	if (c1 == NULL)
	{
		c1 = new Connection(); // Create new connection without params

		if (!c1->Connect()) // Connect to host by socket 
			std::cout << "Cannot connect to host..." << std::endl;
		else
			std::cout << "Connected to host..." << std::endl;
	}
	c1->Close(); // Close connection
}