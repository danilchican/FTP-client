class Control
{
	Connection *c1, *c2;
public:
	Control() : c1(NULL)
	{};
	void setControl(Commands command);
	void setControlWithParams(Commands command, char *params);
	bool haveAny(char *cmd);
};