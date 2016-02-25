class CommandLine
{
	char *cmd;
public:
	void processingStroke(); // will create
	void setCommandLine();
	const char *getRequest(); // return command
private:
	void setData();
};