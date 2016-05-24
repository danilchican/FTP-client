#define _CRT_SECURE_NO_WARNINGS
#include <Winsock.h>
#include <windows.h>
#include <iostream>

enum Commands { CONNECT, DISCONNECT, LIST, DOWNLOAD_FILE, UPLOAD_FILE, DELETE_FILE, RENAME_FILE,
				CURRENT_DIR, MAKE_DIR, MOVE_UP, CHANGE_DIR, DELETE_DIR, HOSTS, ADD_HOST, DELETE_HOST,
				COMMAND_ERROR, CLEAR_CONSOLE, HELP, EXIT };

enum CountParams {
	ONE_PARAM = 1, TWO_PARAMS = 2, THREE_PARAMS = 3, FOUR_PARAMS = 4
};

#define DB_NAME "ftp_db.sqlite"

#define COUNT_COMMANDS 19
#define SIZE_BUFF 1048576

#define PARAMS_NOT_REQUIRED "Parameters aren't required for this command"
#define ONLY_ONE_PARAM "Command have only one param. See \"help\"."
#define DB_NOT_ACCESSABLE "Can't open the database..."

#include "Command.h"
#include "Database.h"
#include "Connection.h"
#include "CommandLine.h"
#include "Control.h"
#include "ResponseHandler.h"
#include "Directory.h"
#include "File.h"
#include "Helper.h"
