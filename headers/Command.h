class Command
{
	
public:
	void static sendCommand(SOCKET sock, const char *command);
	Commands static getCommandByStroke(const char *command);
};