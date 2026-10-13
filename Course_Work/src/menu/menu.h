
#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

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
