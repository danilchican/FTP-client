#include <Winsock.h>
class Connection
{
	char ftpHost[80];
	int port;
	SOCKET sock;

public:
	Connection(char *ftpHost, int port) : port(port)
	{
		strcpy_s(this->ftpHost, ftpHost);
	};
	bool Connect();
};