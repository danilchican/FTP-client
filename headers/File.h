class File
{
	Connection *c1, *c2;
	char *fileName;
	char *arguments;
	char *path;
	long long unsigned int bytes;
public:
	File()
	{};
	File(Connection *c1, Connection *c2, char *params);
private:
	bool find(); // find file on server
	void setFileSize(char *res); // get and set file size in bytes
	bool downloadProcess(); // process wich download file from remote host
	void setPath(); // take path + filename
public:
	bool download(); // download file from server
	static bool hasDirectory(char *params); // save to directory
	static bool checkoutDownloadParams(char *params); // checkout params (three) for downloading
};

// create method for taking path + filename