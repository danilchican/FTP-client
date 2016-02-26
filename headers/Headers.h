#define _CRT_SECURE_NO_WARNINGS
#include <Winsock.h>
#include <windows.h>
#include <iostream>

enum Commands { CONNECT, DISCONNECT, COMMAND_ERROR, CLEAR_CONSOLE, EXIT };

#include "Command.h"
#include "Connection.h"
#include "CommandLine.h"
#include "Control.h"
#include "Checkout.h"
#include "ResponseHandler.h"