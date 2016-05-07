template <class Type>
class Checkout
{
public:
	static Type stroke();
	static Type integer(int from, int to);
	static bool checkCountParams(char *params, CountParams count);
};

template <class Type>
Type  Checkout<Type>::integer(int from, int to) // 0 ... 8080
{
	Type check;

	do{
		cin.clear();
		cin.sync();
		cin >> check;
		if (!cin.good() || check < from || check > to)
			cout << "Incorrect input! Repeat your entering..." << endl;
	} while (!cin.good() || check < from || check > to);

	return check;
}

template <class Type>
Type Checkout<Type>::stroke()
{
	char stroke[80];
	bool flag = true;

	cin.clear(); 
	cin.sync(); 
	cin.get(stroke, 80);

	do {
		int length = strlen(stroke);
		if (cin.good()){
			for (int i = 0; i < length; i++)
			{
				if ((stroke[i] >= 'a' || stroke[i] <= 'z') ||
					(stroke[i] >= 'A' && stroke[i] <= 'Z'))
				{
					flag = false;
					break;
				}
				else
					flag = true;
			}

			if (flag)
			{
				cout << "Repeat your entering!\n";
				cin.clear(); 
				cin.sync(); 
				cin.get(stroke, length + 1);
			}
		}
		else
		{
			cout << "Repeat your entering!\n";
			if (flag)
			{
				cin.clear(); // сбрасываем все биты потока
				cin.sync(); // удаляем данные из буфера
				cin.get(stroke, length + 1);
			}
		}

	} while (flag);

	return stroke;
}

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