class Connection
{
	char ftpHost[80];
	char login[80];
	char password[80];
	unsigned int port;
	unsigned int active_port;
	SOCKET sock;
public:
	Connection();
	Connection(const char *ftpHost, unsigned int port, const char *login, const char *pass);
	bool Connect();
	bool Authorisation(); // to complete for check
	bool Close();
	void ServerResponse();
	void SetPassiveMode();
	void SetIPForActiveMode();
	char * user();
private:
	void quit(); 
};