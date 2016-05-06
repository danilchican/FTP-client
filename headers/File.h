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
	void setPath(); // take path + filename
public:
	bool download(); // download file from server
	bool upload(); // upload file from client to server
	bool _delete(); // Deletes the named file on the remote host
	static bool hasDirectory(char *params); // save to directory
	static bool hasFileInSystem(char *params); // check out file in system
	static bool checkoutDownloadParams(char *params); // checkout params (three) for downloading
	static bool checkoutUploadParams(char *params); // checkout params (two) for uploading
	static bool checkoutDeleteParams(char *params); // checkout params (one) to delete
};