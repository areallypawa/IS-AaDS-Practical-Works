#include <iostream>
#include <Windows.h>
#include "./src/ShuntingYard/ShuntingYard.h"

using namespace std;

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	string expression;

	cout << "Введи выражение: ";
	getline(cin, expression);

	cout << "Постфиксная запись: ";
	cout << shuntingYard(expression) << endl;

	return 0;
}
