class Connection
{
	char ftpHost[80];
	char ipHost[80];
	char login[80];
	char password[80];
	char response[256];
	unsigned int port;
	unsigned int active_port;
	SOCKET sock;
public:
	Connection();
	Connection(const char *ipHost, unsigned int active_port);
	bool Connect();
	bool Authorisation(); // to complete for check
	bool Close();
	char * ServerResponse();
	void SetPassiveMode();
	void SetIPForActiveMode();
	char * user();
	char * IPHost();
	unsigned int activePort();
	SOCKET getSock();
private:
	void quit(); 
};