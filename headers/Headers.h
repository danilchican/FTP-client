#include <Winsock.h>
#include <windows.h>
#include <iostream>

enum Commands { CONNECT, DISCONNECT };

#include "Command.h"
#include "Connection.h"
#include "CommandLine.h"
#include "Control.h"

#define PORT 21


