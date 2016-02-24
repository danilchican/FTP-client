#include <Winsock.h>
class Connection
{
	char ftpHost[80];
	unsigned int port;
	SOCKET sock;
public:
	Connection(const char *ftpHost, unsigned int port);
	bool Connect(); 
	bool Close();
private:
	void quit(); 
};