class Directory
{
public:
	static void currentDirectory(Connection *c1); // display current directory on server
	static void makeDirectory(Connection *c1, char *path); // to complete
	static bool checkoutMakeDirParams(char *params); // checkout one param
	static void changeDirectory(Connection *c1, char *path); // change current directory
};