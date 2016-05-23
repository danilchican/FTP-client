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
	Connection() 
	{};
	Connection(Database * db);
	Connection(const char *ipHost, unsigned int active_port);
	bool connectToServer(); // connect to server
	bool authorisation(); // to complete for check
	bool close(); // close server connection
	char * serverResponse(); // response from server
	void closeSocket(); // close socket
	bool setPassiveMode(); 
	bool setIPForActiveMode();
	char * user(); // return username
	char * getIPHost(); // return ipHost
	unsigned int activePort(); // return active port for transfering data
	SOCKET getSock(); // return current socket
private:
	void quit(); // send QUIT command to server for closing connection
};