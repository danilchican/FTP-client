class Command
{
public:
	static void sendCommand(SOCKET sock, const char *command); // sending command to server
	static Commands getCommandByStroke(char *command, bool haveParams); // return enum command
	static char * getCommandLineArguments(char *cmd); // return command arguments
	static bool haveAnyArgs(char *cmd); // checkout if having any params in command line
	static bool checkCountParams(char *params, CountParams count);
};