#pragma comment(lib, "wsock32.lib")

#include <Winsock.h>
#include <windows.h>
#include <iostream>

#include "headers\Connection.h"
#include "headers\Command.h"

#define PORT 21

WSADATA ws;
char buf[256];