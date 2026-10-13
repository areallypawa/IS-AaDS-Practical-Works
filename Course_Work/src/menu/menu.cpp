
#include "menu.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>

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

    std::cout
        << "=============== "
        << str
        << " ===============\n";

    for (int i = 0; i < size_items; i++) {
        if (i == current) {
            std::cout
                << " -> "
                << items[i]
                << "   \n";
        }
        else {
            std::cout
                << "    "
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
