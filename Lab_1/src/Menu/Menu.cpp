#include "Menu.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <sstream>

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(10000000, '\n');
}

void pause() {
    std::cout << "\nНажмите любую клавишу для продолжения...";
    _getch();
}

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    cursorInfo.bVisible = false;

    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void showCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    cursorInfo.bVisible = true;

    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void set_cords(int x, int y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos = {
        static_cast<SHORT>(x),
        static_cast<SHORT>(y)
    };

    SetConsoleCursorPosition(hStdout, pos);
}

void show_menu(
    int current,
    int size_items,
    const std::string items[],
    const std::string& str
) {
    hideCursor();

    set_cords(0, 0);

    std::cout << "=============== "
        << str
        << " ===============\n";

    for (int i = 0; i < size_items; i++) {
        if (i == current) {
            std::cout << " -> "
                << items[i]
                << "   \n";
        }
        else {
            std::cout << "    "
                << items[i]
                << "   \n";
        }
    }
}

int run_menu(
    const std::string items[],
    int size_items,
    const std::string& title
) {
    int current = 0;

    clear();

    while (true) {
        show_menu(
            current,
            size_items,
            items,
            title
        );

        int key = _getch();

        if (key == 224) {
            key = _getch();

            if (key == 72 && current > 0)
                current--;

            if (key == 80 && current < size_items - 1)
                current++;
        }
        else if (key == 13) {
            return current;
        }
    }
}

void interact_with_stack(Stack<int>& container) {
    const int countItems = 6;

    std::string items[countItems] = {
        "Заполнить случайными числами",
        "Заполнить вручную (через пробел)",
        "Добавить элемент (push)",
        "Удалить элемент (pop)",
        "Показать верхний (top)",
        "Назад"
    };

    while (true) {
        int choice = run_menu(
            items,
            countItems,
            "РАБОТА СО СТЕКОМ"
        );

        clear();
        showCursor();

        bool modified = false;

        if (choice == 0) {
            int n;

            std::cout << "Введите количество случайных чисел: ";
            std::cin >> n;

            for (int i = 0; i < n; i++)
                container.push(rand() % 100);

            modified = true;
        }
        else if (choice == 1) {
            std::cout << "Введите числа через пробел: ";

            if (std::cin.peek() == '\n')
                std::cin.ignore();

            std::string line;
            std::getline(std::cin, line);

            std::stringstream ss(line);
            int num;

            while (ss >> num)
                container.push(num);

            modified = true;
        }
        else if (choice == 2) {
            int val;

            std::cout << "Введите значение для push: ";
            std::cin >> val;

            container.push(val);
            modified = true;
        }
        else if (choice == 3) {
            if (!container.empty()) {
                container.pop();
                modified = true;
            }
            else {
                std::cout << "Ошибка: Стек пуст!\n";
            }
        }
        else if (choice == 4) {
            if (!container.empty()) {
                std::cout
                    << "Верхний элемент (top): "
                    << container.top()
                    << "\n";
            }
            else {
                std::cout << "Стек пуст!\n";
            }
        }
        else if (choice == 5) {
            break;
        }

        if (modified)
            print_updated_state(container, "Стек");

        pause();
    }
}