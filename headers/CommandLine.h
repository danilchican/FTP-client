class CommandLine
{
	char *cmd;
public:
	void setCommandLine(); // setting up command line
	char *getRequest(); // return command from commandline
private:
	void setData();
};