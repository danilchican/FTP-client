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
	bool find(Commands com); // find file on server
	void setFileSize(char *res, bool is_download); // get and set file size in bytes
	bool downloadProcess(); // process wich download file from remote host
	bool uploadProcess(); // process wich upload file from client to the remote host
	bool deleteProcess(); // process wich delete the named file on the remote host
	bool renameProcess(); // process wich rename file on the remote host
	void setPath(); // take path + filename
public:
	bool download(); // download file from server
	bool upload(); // upload file from client to server
	bool _delete(); // deletes the named file on the remote host
	bool rename(); // rename the file on the remote host
	static bool hasDirectory(char *params); // save to directory
	static bool hasFileInSystem(char *params); // check out file in system
	static bool checkCountParams(char *params, CountParams count); // checkout count params for process
};