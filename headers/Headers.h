#pragma comment(lib, "wsock32.lib")

#include <Winsock.h>
#include <windows.h>
#include <iostream>

#include "Connection.h"
#include "Command.h"
#include "CommandLine.h"
#include "Control.h"

#define PORT 21

WSADATA ws;
char buf[256];