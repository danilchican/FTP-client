class CommandLine
{
	char *cmd;
public:
	void processingStroke(); // to complete
	void setCommandLine();
	const char *getRequest(); // return command
private:
	void setData();
	/*
		- connect, 
		- disconnect
	*/
};