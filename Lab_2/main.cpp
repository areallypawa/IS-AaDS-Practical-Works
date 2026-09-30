#include <iostream>
#include "src/Menu/Menu.h"

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    const int countItems = 2;

    std::string items[countItems] = {
        "Работа с TimSort",
        "Выход"
    };

    while (true) {
        int choice = run_menu(
            items,
            countItems,
            "ЛАБОРАТОРНАЯ РАБОТА №2"
        );

        clear();
        showCursor();

        if (choice == 0) {
            interact_with_tim_sort();
        }
        else {
            break;
        }

    }

    showCursor();
    clear();

    std::cout << "Программа завершена.\n";

    return 0;
}