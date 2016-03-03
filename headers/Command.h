class Command
{
public:
	static void sendCommand(SOCKET sock, const char *command);
	static Commands getCommandByStroke(const char *command);
};