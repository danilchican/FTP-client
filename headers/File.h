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
	bool find(bool is_upload); // find file on server
	void setFileSize(char *res, bool is_download); // get and set file size in bytes
	bool downloadProcess(); // process wich download file from remote host
	bool uploadProcess(); // process wich upload file from client to the remote host
	void setPath(); // take path + filename
public:
	bool download(); // download file from server
	bool upload(); // upload file from client to server                               take it
	static bool hasDirectory(char *params); // save to directory
	static bool hasFileInSystem(char *params); // check out file in system
	static bool checkoutDownloadParams(char *params); // checkout params (three) for downloading
	static bool checkoutUploadParams(char *params); // checkout params (two) for uploading
};