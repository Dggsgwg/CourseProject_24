#include <iostream>
#include <format>
#include "Spreadsheet.h"
#include "Menu.h"


using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    Record r = Record("ИТ22-2",1,format("Ф И О1"), false, format("очная"), Date(2001,1,1), Date(2021, 1, 1), 250);
    Record r2 = Record("ИТ22-3", 2, format("Ф И О2"), true, format("очная"), Date(2002, 1, 1), Date(2021, 1, 1), 250);
    Record r3 = Record("ИТ22-4", 3, format("Ф И О3"), false, format("очная"), Date(2003, 1, 1), Date(2021, 1, 1), 250);
    Record r4 = Record("ИТ22-5", 4, format("Ф И О4"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250);
    Record r5 = Record("ИТ22-6", 5, format("Ф И О5"), true, format("очная"), Date(2005, 1, 1), Date(2021, 1, 1), 250);
    Record r6 = Record("ИТ22-6", 6, format("Ф И О5"), true, format("очная"), Date(2006, 1, 1), Date(2021, 1, 1), 250);
    Record r7 = Record("ИТ22-6", 7, format("Ф И О5"), false, format("очная"), Date(2007, 1, 1), Date(2021, 1, 1), 250);
    Record r8 = Record("ИТ22-6", 8, format("Ф И О5"), true, format("очная"), Date(2008, 1, 1), Date(2021, 1, 1), 250);
    Node* list = new Node(r, NULL);
    Spreadsheet s = Spreadsheet("Таблица", NULL);
    //s.display();
    /*s.addRecord(r);
    s.addRecord(r2);
    s.addRecord(r3);
    s.addRecord(r4);
    s.addRecord(r5);
    s.addRecord(r6);
    s.addRecord(r7);
    s.addRecord(r8);*/
    //s.saveToFile("test");
    //s.display();
    //s.sort();
    //s.editRecord("ИТ22-5", Record("qqqqqq",123, format("Ф И О"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250));
    //Node* res = s.seek(123456);
    //cout << res->toString() << endl;
    //s.display();
    //s.removeRecord("ИТ22-6");
    //s.display();
    //s.readFromFile("test");
    //s.getFiveEldest();
    //s.display();

    //Menu m = Menu();
    //m.init();
}