class File
{
	Connection *c1, *c2;
	char *fileName;
	char *arguments;
	long long unsigned int bytes;
public:
	File()
	{};
	File(Connection *c1, Connection *c2, char *params);
	bool download(); // download file from server
private:
	bool find(); // find file on server
	void setFileSize(char *res); // get and set file size in bytes
	bool downloadProcess(); // process wich download file from remote host
};