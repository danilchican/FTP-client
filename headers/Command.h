class Command
{
public:
	static void sendCommand(SOCKET sock, const char *command);
	static Commands getCommandByStroke(char *command, bool haveParams);
	static char * getCommandLineArguments(char *cmd);
};