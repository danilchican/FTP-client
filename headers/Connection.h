class Connection
{
	char ftpHost[80];
	char login[80];
	char password[80];
	unsigned int port;
	SOCKET sock;
public:
	Connection();
	Connection(const char *ftpHost, unsigned int port, const char *login, const char *pass);
	bool Connect();
	bool Authorisation();
	bool Close();
private:
	void quit(); 
};