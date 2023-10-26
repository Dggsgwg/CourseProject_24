#include <iostream>
#include <format>
#include "Spreadsheet.h"


using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    Record r = Record("ИТ22-2",12345,format("Ф И О"), true, format("очная"), Date(2004,1,1), Date(2021, 1, 1), 250);
    Record r2 = Record("ИТ22-3", 12345, format("Ф И О"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250);
    Record r3 = Record("ИТ22-4", 12345, format("Ф И О"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250);
    Record r4 = Record("ИТ22-5", 123456, format("Ф И О"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250);
    Record r5 = Record("ИТ22-6", 12345, format("Ф И О"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250);
    Node* list = new Node(r, NULL);
    Spreadsheet s = Spreadsheet("Таблица", list);
    s.display();
    s.addRecord(r2);
    s.addRecord(r3);
    s.addRecord(r4);
    s.addRecord(r5);
    s.display();
    //s.sort();
    //s.editRecord("ИТ22-5", Record("qqqqqq",123, format("Ф И О"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250));
    //Node* res = s.seek(123456);
    //cout << res->toString() << endl;
    //s.display();
    //s.removeRecord("ИТ22-6");
    //s.display();
    //s.saveToFile("test");
    s.readFromFile("test");
}