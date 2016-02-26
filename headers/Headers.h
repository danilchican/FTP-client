#include <Winsock.h>
#include <windows.h>
#include <iostream>

enum Commands { CONNECT, DISCONNECT, COMMAND_ERROR, CLEAR_CONSOLE };

#include "Command.h"
#include "Connection.h"
#include "CommandLine.h"
#include "Control.h"

#define PORT 21


