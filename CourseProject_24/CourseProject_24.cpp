#include <iostream>
#include <format>
#include <Windows.h>
#include "Menu.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);

    Menu m = Menu();
    m.start();
}