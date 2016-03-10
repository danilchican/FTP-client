#define _CRT_SECURE_NO_WARNINGS
#include <Winsock.h>
#include <windows.h>
#include <iostream>

enum Commands { CONNECT, DISCONNECT, STATUS, LIST,
				CURRENT_DIR, MAKE_DIR, MOVE_UP, CHANGE_DIR, DELETE_DIR,
				COMMAND_ERROR, CLEAR_CONSOLE, HELP, EXIT };

#define COUNT_COMMANDS 12
#define SIZE_BUFF 256
#define PARAMS_NOT_REQUIRED "Parameters aren't required for this command"
#define ONLY_ONE_PARAM "Command have only one param. See -help."

#include "Command.h"
#include "Connection.h"
#include "CommandLine.h"
#include "Control.h"
#include "Checkout.h"
#include "ResponseHandler.h"
#include "Directory.h"
#include "Helper.h"