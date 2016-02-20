#include <Winsock.h>
class Connection
{
	char ftpHost[80];
	int port;
	SOCKET sock;
public:
	Connection(char *ftpHost, int port);
	bool Connect(); 
	bool Close(); // to complete	
private:
	void quit(); // send command QUIT
	void sendCommand(const char *command); // send some commands 
};