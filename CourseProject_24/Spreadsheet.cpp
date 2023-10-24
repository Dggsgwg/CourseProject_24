#include <iostream>
#include "Spreadsheet.h"

using namespace std;

Spreadsheet::Spreadsheet(string _tableName) 
{
	tableName = _tableName;
}

Spreadsheet::Spreadsheet(string _tableName, Node* _list) 
{
	tableName = _tableName;
	list = _list;
}

void Spreadsheet::display() 
{
	cout << "Таблица: " << tableName << endl;
	Node* showList = list;

	if (list != NULL) 
	{
		do {
			cout << showList->toString() << endl;
			showList = showList->next;
		} while (showList != NULL);
	}
	else 
	{
		cout << "Таблица пуста." << endl;
	}

	delete showList;
	showList = nullptr;
}

void Spreadsheet::addRecord(Record record) 
{
	Node* newElem = new Node(record, list);
	list = newElem;

	newElem = nullptr;
}