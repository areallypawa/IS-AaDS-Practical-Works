#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <conio.h>

#include "../Stack/Stack.h"

void clear();
void clearInput();
void pause();

void hideCursor();
void showCursor();
void set_cords(int x, int y);

void show_menu(
    int current,
    int size_items,
    const std::string items[],
    const std::string& str
);

int run_menu(
    const std::string items[],
    int size_items,
    const std::string& title
);

template <typename T>
void print_updated_state(
    T& container,
    const std::string& structName
) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 10);

    std::cout << "\n"
        << structName
        << " после операции:\n";

    SetConsoleTextAttribute(hConsole, 7);

    if (container.empty()) {
        std::cout << "(пусто)\n";
    }
    else {
        container.print();
    }
}

template <typename T>
void interact_with_list_or_array(
    T& container,
    const std::string& title,
    const std::string& structName
) {
    const int countItems = 7;

    std::string items[countItems] = {
        "Заполнить случайными числами",
        "Заполнить вручную (через пробел)",
        "Добавить в конец (push_back)",
        "Добавить в начало (push_front)",
        "Удалить с конца (pop_back)",
        "Удалить с начала (pop_front)",
        "Назад"
    };

    while (true) {
        int choice = run_menu(
            items,
            countItems,
            title
        );

        clear();
        showCursor();

        bool modified = false;

        if (choice == 0) {
            int n;

            std::cout << "Введите количество случайных чисел: ";
            std::cin >> n;

            for (int i = 0; i < n; i++) {
                container.push_back(rand() % 100);
            }

            modified = true;
        }
        else if (choice == 1) {
            std::cout << "Введите числа через пробел: ";

            if (std::cin.peek() == '\n') {
                std::cin.ignore();
            }

            std::string line;
            std::getline(std::cin, line);

            std::stringstream ss(line);
            int num;

            while (ss >> num) {
                container.push_back(num);
            }

            modified = true;
        }
        else if (choice == 2) {
            int val;

            std::cout << "Введите значение для push_back: ";
            std::cin >> val;

            container.push_back(val);
            modified = true;
        }
        else if (choice == 3) {
            int val;

            std::cout << "Введите значение для push_front: ";
            std::cin >> val;

            container.push_front(val);
            modified = true;
        }
        else if (choice == 4) {
            if (!container.empty()) {
                container.pop_back();
                modified = true;
            }
            else {
                std::cout << "Ошибка: Структура пуста!\n";
            }
        }
        else if (choice == 5) {
            if (!container.empty()) {
                container.pop_front();
                modified = true;
            }
            else {
                std::cout << "Ошибка: Структура пуста!\n";
            }
        }
        else if (choice == 6) {
            break;
        }

        if (modified) {
            print_updated_state(
                container,
                structName
            );
        }

        pause();
    }
}

void interact_with_stack(Stack<int>& container);