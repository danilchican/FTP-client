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
	bool Connect(); // connect to server
	void Reconnect(); // reconnect to server
	bool Authorisation(); // to complete for check
	bool Close(); // close server connection
	char * ServerResponse(); // response from server
	void CloseSocket(); // close socket
	bool SetPassiveMode(); 
	bool SetIPForActiveMode();
	char * user(); // return username
	char * IPHost(); // return ipHost
	unsigned int activePort(); // return active port for transfering data
	SOCKET getSock(); // return current socket
private:
	void quit(); // send QUIT command to server for closing connection
};