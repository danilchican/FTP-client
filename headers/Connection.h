#include <Winsock.h>
class Connection
{
	char ftpHost[80];
	int port;
	SOCKET sock;
public:
	Connection(char *ftpHost, int port);
	bool Connect();
	bool CloseConnection(); // to complete
};