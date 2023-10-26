#include <iostream>
#include <fstream>
#include <format>
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

bool Spreadsheet::removeRecord(const char* groupCode) 
{
	Node* head = list;

	if (head != NULL)
	{
		if (strcmp(list->record.groupCode, groupCode) == 0) 
		{
			list = list->next;
		}
		while (head->next) {
			if (strcmp(head->next->record.groupCode, groupCode) == 0) 
			{
				if (head->next->next != NULL) 
				{
					head->next = head->next->next;
					return true;
				}
				else
				{
					head->next = NULL;
					return true;
				}
			}
			head = head->next;
		} 
	}

	return false;
}

bool Spreadsheet::editRecord(const char* groupCode, Record record) 
{
	Node* head = list;

	if (head != NULL)
	{
		while (head) {
			if (strcmp(head->record.groupCode, groupCode) == 0)
			{
				head->record = record;

				head = nullptr;
				return true;
			}

			head = head->next;
		}
	}

	head = nullptr;
	return false;
}

void Spreadsheet::sort() //пузырьковая сортировка
{
	Node* t, * m, * a, * b;
	if (list == NULL) return;

	for (bool go = true; go; ) {
		go = false;
		a = t = list;
		b = list->next;

		while (b != NULL) {
			if (a->record > b->record) {
				if (t == a)
					list = b;
				else
					t->next = b;

				a->next = b->next;
				b->next = a;

				m = a, a = b, b = m;
				go = true;
			}
			t = a;
			a = a->next;
			b = b->next;
		}
	}

	t = m = a = b = nullptr;
}

Node* Spreadsheet::seek(int personalId) 
{
	Node* head = list;
	
	while (head) 
	{
		if (head->record.personalId == personalId) 
		{
			return head;
		}

		head = head->next;
	}

	return NULL;
}

void Spreadsheet::saveToFile(string fileName) 
{
	ofstream out;
	out.open(format("{}.sheet",fileName));

	cout << out.is_open() << endl;
	if (out.is_open())
	{
		while (list)
		{
			out << list->toFileString() << endl;
			list = list->next;
		}
	}
}

istream& operator >>(istream& in, Record& r)
{
	string group, birthday, entrance;
	cout << "suc" << endl;
	in >> group >> r.personalId >> r.name >> r.isMale >> r.educationForm >> birthday >> entrance;
	cout << "suc" << endl;
	return in;
}

void Spreadsheet::readFromFile(string fileName)
{
	ifstream in(format("{}.sheet", fileName));
	string line;
	Record r = Record();
	in >> r;

	cout << r.toString();
	if (in.is_open()) 
	{
		while (getline(in, line)) 
		{
			
		}
	}

}