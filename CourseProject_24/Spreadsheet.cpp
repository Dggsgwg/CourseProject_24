#include <iostream>
#include <fstream>
#include <format>
#include <conio.h>
#include <Windows.h>
#include <dos.h>
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

void Spreadsheet::printHeader() 
{
	cout << "+-------------+------------+---------------------+---------+-------------+------------+------------------+-----------+" << endl
		<< "| ���� ������ | ����� ���. |         ���         |   ���   | ����� ����. | ���� ����. | ���� ����������� | ����� ��� |" << endl
		<< "+-------------+------------+---------------------+---------+-------------+------------+------------------+-----------+" << endl;
}

void cursor(int size) {
	bool exit = false;
	int ch;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 1, 14 };
	SetConsoleCursorPosition(hConsole, position);

	while (true) {
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
	}

	while (!exit)
	{
		ch = _getch();
		switch (ch)
		{
		case 224:
		{
			switch (_getch())
			{
			case 72:
			{// ������ ������� �����
				if (position.Y)
				{
					position.Y--;
					SetConsoleCursorPosition(hConsole, position);
					cout << (char)16;
					SetConsoleCursorPosition(hConsole, position);
				}
				else 
				{
					
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD pos = { position.X, 0 };
					SetConsoleCursorPosition(hConsole, pos);
				}
				break;
			}
			case 80:
			{// ������ ������� ����
				if (position.Y < size)
				{
					position.Y++;
					SetConsoleCursorPosition(hConsole, position);
					cout << (char)16;
					SetConsoleCursorPosition(hConsole, position);
				}
				break;
			}
			case 75:
			{// ������ ������� �����
				if (position.X)
				{
					position.X--;
					SetConsoleCursorPosition(hConsole, position);
					cout << (char)16;
					SetConsoleCursorPosition(hConsole, position);
				}
				break;
			}
			case 77:
			{// ������ ������� ������
				if (position.X < 119)
				{
					position.X++;
					SetConsoleCursorPosition(hConsole, position);
					cout << (char)16;
					SetConsoleCursorPosition(hConsole, position);
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		case 27:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
	}
}

void Spreadsheet::display()
{
	cout << "�������: " << tableName << endl;
	printHeader();

	Node* showList = list;

	if (list != NULL)
	{
		do {
			cout << showList->toString() << endl;
			showList = showList->next;
		} while (showList != NULL);
		cout << "+-------------+------------+---------------------+---------+-------------+------------+------------------+-----------+" << endl;
	}
	else
	{
		cout << "������� �����." << endl;
	}

	cursor(40);

	delete showList;
	showList = nullptr;
}

void Spreadsheet::addRecord(Record record)
{
	Node* newElem = new Node(record, list);
	list = newElem;

	newElem = nullptr;
}

Record Spreadsheet::getRecordFromStream(istream& in)
{
	Record r;
	in >> r;
	
	return r;
}

bool Spreadsheet::removeRecord(int personalId)
{
	Node* head = list;

	if (head != NULL)
	{
		if (list->record.personalId == personalId)
		{
			list = list->next;
			return true;
		}
		while (head->next) {
			if (head->next->record.personalId == personalId)
			{
				head->next = head->next->next;
				return true;
			}
			head = head->next;
		}
	}

	return false;
}

bool Spreadsheet::editRecord(int personalId, Record record)
{
	Node* head = list;

	if (head != NULL)
	{
		while (head) {
			if (head->record.personalId == personalId)
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

void Spreadsheet::sort() //����������� ����������
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

	while (head)
	{
		if (head->record.isMale == isMale) {
			if (count < 5) {
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
		}
		head = head->next;
	}

	head = nullptr;
}

void Spreadsheet::getFiveEldest()
{
	Node** males = new Node * [5] {};
	Node** females = new Node * [5] {};

	getFiveEldest(males, true);
	getFiveEldest(females, false);

	cout << "C������ �����:" << endl;
	printHeader();

	for (int i = 0; i < 5; i++)
	{
		if (males[i])
			cout << males[i]->toString() << endl;
	}
	cout << "+-------------+------------+---------------------+---------+-------------+------------+------------------+-----------+" << endl;

	cout << endl << "C������ �������:" << endl;
	printHeader();
	for (int i = 0; i < 5; i++)
	{
		if (females[i])
			cout << females[i]->toString() << endl;
	}
	cout << "+-------------+------------+---------------------+---------+-------------+------------+------------------+-----------+" << endl;

	delete males, females;
	males = females = nullptr;
}

void Spreadsheet::saveToFile(string fileName)
{
	ofstream out;
	out.open(format("{}.bin", fileName));
	Node* head = list;

	if (out.is_open())
	{
		while (head)
		{
			out << head->toFileString() << endl;
			head = head->next;
		}
	}

	head = nullptr;
}

void Spreadsheet::readFromFile(string fileName)
{
	tableName = fileName;
	ifstream in(format("{}.sheet", fileName));
	Record r = Record();

	if (in.is_open())
	{
		while (in >> r)
		{
			addRecord(r);
		}
	}
}