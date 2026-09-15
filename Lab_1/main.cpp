#include <iostream>
#include "src/linkedList/linked_list.h"
#include <Windows.h>
using namespace std;

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	LinkedList<int> listi;
	
	listi.push_back(1);
	listi.push_back(2);
	listi.push_back(3);

	listi.push_front(0);

	cout << "Лист после:" << endl;
	listi.print_list();

	listi.pop_front();
	listi.pop_back();

	cout << "Лист после:";
	listi.print_list();

	return 0;
}