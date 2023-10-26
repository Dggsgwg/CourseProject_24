#include <iostream>
#include <fstream>
#include <format>
#include "Spreadsheet.h"

using namespace std;

Spreadsheet::Spreadsheet() 
{
	tableName = "";
	list = NULL;
}

Spreadsheet::Spreadsheet(string _tableName)
{
	tableName = _tableName;
	list = NULL;
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

bool Spreadsheet::removeRecord(string groupCode)
{
	Node* head = list;

	if (head != NULL)
	{
		if (strcmp(list->record.groupCode.c_str(), groupCode.c_str()) == 0)
		{
			list = list->next;
		}
		while (head->next) {
			if (strcmp(head->next->record.groupCode.c_str(), groupCode.c_str()) == 0)
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

bool Spreadsheet::editRecord(string groupCode, Record record)
{
	Node* head = list;

	if (head != NULL)
	{
		while (head) {
			if (strcmp(head->record.groupCode.c_str(), groupCode.c_str()) == 0)
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

void Spreadsheet::getFiveEldest(Node** array, bool isMale)
{
	Node* head = list;
	int count = 0;
	Date minDate = Date(3000, 1, 1);

	while (head)
	{
		if (head->record.isMale == isMale) {
			if (head->record.birthdayDate.compare(minDate) < 0)
			{
				if (count <= 4) {
					array[count] = head;
					count++;
				}
				else {
					Date maxArrDate = Date(1, 1, 1);
					int index;
					for (int i = 0; i < 5; i++)
					{
						if (array[i]->record.birthdayDate.compare(maxArrDate) > 0)
						{
							maxArrDate = array[i]->record.birthdayDate;
							index = i;
						}
					}
					array[index] = head;
				}
				minDate = head->record.birthdayDate;
			}
		}
		head = head->next;
	}
}

void Spreadsheet::getFiveEldest()
{
	Node** males = new Node* [5] {};
	Node** females = new Node* [5] {};
	
	getFiveEldest(males, true);
	getFiveEldest(females, false);

	for (int i = 0; i < 5; i++) 
	{
		if (males[i])
		cout << "m - " << males[i]->toString() << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < 5; i++)
	{
		if(females[i])
		cout << "f - " << females[i]->toString() << endl;
	}

}

void Spreadsheet::saveToFile(string fileName)
{
	ofstream out;
	out.open(format("{}.sheet", fileName));
	Node* head = list;

	if (out.is_open())
	{
		while (head)
		{
			out << head->toFileString() << endl;
			head = head->next;
		}
	}

	delete head;
	head = nullptr;
}

istream& operator >> (istream& in, Record& r)
{
	string isMale, firstName, middleName, lastName;
	in >> r.groupCode >> r.personalId >> firstName >> middleName >> lastName >> isMale 
		>> r.educationForm >> r.birthdayDate.day >> r.birthdayDate.month 
		>> r.birthdayDate.year >> r.entranceDate.day >> r.entranceDate.month 
		>> r.entranceDate.year >> r.EGEPoints;
	r.isMale = (strcmp(isMale.c_str(), "true") == 0) ? true : false;
	r.name = format("{} {} {}", firstName, middleName, lastName);

	return in;
}

void Spreadsheet::readFromFile(string fileName)
{
	ifstream in(format("{}.sheet", fileName));
	Record r = Record();

	//cout << r.toString();
	if (in.is_open())
	{
		while (in >> r)
		{
			addRecord(r);
		}
	}
}