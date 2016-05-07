template <class Type>
class Checkout
{
public:
	static Type stroke();
	static Type integer(int from, int to);
	static bool checkCountParams(char *params, CountParams count);
};

template <class Type>
bool Checkout<Type>::checkCountParams(char *params, CountParams count)
{
	int countArguments = 0;

	char *arg = new char[strlen(params) + 1];
	strcpy(arg, params);

	char *pch = strtok(arg, ",");

	for (countArguments = 0; pch != NULL; countArguments++) {
		pch = strtok(NULL, ",");
	}

	return (countArguments == count) ? true : false;
}