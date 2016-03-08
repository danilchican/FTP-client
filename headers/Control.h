class Control
{
	Connection *c1, *c2;
public:
	Control() : c1(NULL)
	{};
	void setControl(Commands command); // set control between commands and methods if haven't any params
	void setControlWithParams(Commands command, char *params); // set control between commands and method if have any params
	bool haveAny(char *cmd); // checkout if having any params in command line
};