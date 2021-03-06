class Directory
{
public:
	static void currentDirectory(Connection *c1); // display current directory on server
	static char * processingCurrentDirectory(char *resp); // processing server response stroke with directory
	static void moveUp(Connection *c1); // Moves up to the parent directory
	static void makeDirectory(Connection *c1, char *path); // to complete
	static void changeDirectory(Connection *c1, char *path); // change current directory
	static void removeDirectory(Connection *c1, char *path); // remove the remote directory
	static void list(Connection *c1, Connection *c2);
};