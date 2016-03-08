class Command
{
public:
	static void sendCommand(SOCKET sock, const char *command); // sending command to server
	static Commands getCommandByStroke(char *command, bool haveParams); // return enum command
	static char * getCommandLineArguments(char *cmd); // return command arguments
};