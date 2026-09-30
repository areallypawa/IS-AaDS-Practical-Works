#include <iostream>
#include <string>
#include <Windows.h>

#include "src/DoubleLinkedList/DoubleLinkedList.h"
#include "src/DynamicArray/DynamicArray.h"
#include "src/Stack/Stack.h"
#include "src/Menu/Menu.h"
#include "src/ShuntingYard/ShuntingYard.h"

using namespace std;


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    srand(static_cast<unsigned>(time(nullptr)));

    DoubleLinkedList<int> list;
    DynamicArray<int> array;
    Stack<int> stack;

    const int mainCount = 5;
    string mainItems[mainCount] = {
        "Двусвязный список (DoubleLinkedList)",
        "Динамический массив (DynamicArray)",
        "Стек (Stack)",
        "Сортировочная станция (Shunting Yard)",
        "Выход"
    };

    while (true) {
        int choice = run_menu(mainItems, mainCount, "ГЛАВНОЕ МЕНЮ");

        if (choice == 0) {
            interact_with_list_or_array(list, "МЕНЮ: ДВУСВЯЗНЫЙ СПИСОК", "Список");
        }
        else if (choice == 1) {
            interact_with_list_or_array(array, "МЕНЮ: ДИНАМИЧЕСКИЙ МАССИВ", "Массив");
        }
        else if (choice == 2) {
            interact_with_stack(stack);
        }
        else if (choice == 3) {
            clear();
            showCursor();
            cout << "=============== СОРТИРОВОЧНАЯ СТАНЦИЯ ===============\n";
            cout << "Введи выражение: ";
            if (cin.peek() == '\n') cin.ignore();
            string expr;
            getline(cin, expr);

            cout << "Постфиксная запись: ";

            // Красим результат в зеленый
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);
            cout << shuntingYard(expr) << endl;
            SetConsoleTextAttribute(hConsole, 7);

            pause();
        }
        else if (choice == 4) {
            clear();
            showCursor();
            cout << "Завершение программы...\n";
            break;
        }
    }

    return 0;
}