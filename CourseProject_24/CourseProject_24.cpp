#include <iostream>
#include <format>
#include "Spreadsheet.h"



using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    Record r = Record("ИТ22-2",12345,format("Ф И О"), true, format("очная"), Date(2004,1,1), Date(2021, 1, 1), 250);
    Node* list = new Node(r, NULL);
    Spreadsheet s = Spreadsheet("Таблица", list);
    s.display();
    s.addRecord(r);
    s.display();
}