class Command
{
	
public:
	void static sendCommand(SOCKET sock, char *command);
	Commands static getCommandByStroke(const char *command);
};