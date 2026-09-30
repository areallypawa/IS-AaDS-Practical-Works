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


// ============================================================
//                         TIM SORT
// ============================================================

void interact_with_tim_sort() {
    int* array = nullptr;
    int size = 0;

    const int countItems = 5;

    std::string items[countItems] = {
        "Заполнить случайными числами",
        "Заполнить вручную (через пробел)",
        "Показать массив",
        "Выполнить TimSort",
        "Назад"
    };

    while (true) {
        int choice = run_menu(
            items,
            countItems,
            "РАБОТА С TIM SORT"
        );

        clear();
        showCursor();

        if (choice == 0) {
            if (array != nullptr) {
                delete[] array;
                array = nullptr;
            }

            std::cout << "Введите количество элементов: ";
            std::cin >> size;

            if (size <= 0) {
                std::cout << "Ошибка: размер должен быть больше 0!\n";
                size = 0;
            }
            else {
                array = new int[size];

                for (int i = 0; i < size; i++)
                    array[i] = rand() % 100;

                std::cout << "\nМассив заполнен:\n";

                for (int i = 0; i < size; i++)
                    std::cout << array[i] << " ";

                std::cout << "\n";
            }
        }
        else if (choice == 1) {
            if (array != nullptr) {
                delete[] array;
                array = nullptr;
            }

            std::cout << "Введите числа через пробел:\n";

            if (std::cin.peek() == '\n')
                std::cin.ignore();

            std::string line;
            std::getline(std::cin, line);

            std::stringstream ss(line);

            int tempSize = 0;
            int value;

            while (ss >> value)
                tempSize++;

            if (tempSize == 0) {
                std::cout << "Ошибка: массив пуст!\n";
            }
            else {
                delete[] array;

                array = new int[tempSize];
                size = tempSize;

                ss.clear();
                ss.str(line);

                for (int i = 0; i < size; i++)
                    ss >> array[i];

                std::cout << "\nМассив заполнен:\n";

                for (int i = 0; i < size; i++)
                    std::cout << array[i] << " ";

                std::cout << "\n";
            }
        }
        else if (choice == 2) {
            if (array == nullptr || size == 0) {
                std::cout << "Массив пуст!\n";
            }
            else {
                std::cout << "Текущий массив:\n";

                for (int i = 0; i < size; i++)
                    std::cout << array[i] << " ";

                std::cout << "\n";
            }
        }
        else if (choice == 3) {
            if (array == nullptr || size == 0) {
                std::cout
                    << "Ошибка: сначала заполните массив!\n";
            }
            else {
                std::cout << "Массив до TimSort:\n";

                for (int i = 0; i < size; i++)
                    std::cout << array[i] << " ";

                std::cout << "\n";

                TimSort timSort(array, size);

                timSort.sort();

                std::cout << "\nМассив после TimSort:\n";

                timSort.print();
            }
        }
        else if (choice == 4) {
            break;
        }

        if (choice != 4)
            pause();
    }

    delete[] array;
}