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
	cout << "+-------------+------------+---------------------+-----+-------------+------------+------------------+-----------+" << endl
		 << "| Шифр группы | Номер зач. |         ФИО         | Пол | Форма обуч. | Дата рожд. | Дата поступления | Баллы ЕГЭ |" << endl
	   	 << "+-------------+------------+---------------------+-----+-------------+------------+------------------+-----------+" << endl;
}

void Spreadsheet::printBottom() 
{
	cout << "+-------------+------------+---------------------+-----+-------------+------------+------------------+-----------+" << endl;
}

int Spreadsheet::compareDate(Date date, Date date2) 
{
	if (date.year > date2.year) return  1;
	else if (date.year < date2.year) return -1;
	if (date.month > date2.month) return 1;
	else if (date.month < date2.month) return -1;
	if (date.day > date2.day) return 1;
	else if (date.day < date2.day) return -1;
	else return 0;
}

string Spreadsheet::dateToString(Date date) 
{
	return format("{:02}.{:02}.{}", date.day, date.month, date.year);
}

string Spreadsheet::dateToFileString(Date date) 
{
	return format("{} {} {}", date.day, date.month, date.year);
}

bool operator > (const Record& record, const Record& record2) 
{
	return strcmp(record.groupCode.c_str(), record2.groupCode.c_str()) > 0;
}

string Spreadsheet::recordToString(Record record) 
{
	return format("|   {:<9} | {:<10} | {:<19} |  {:<1}  |   {:<9} | {:<10} |    {:<13} |    {:<6} |",
		record.groupCode, record.personalId, record.name, record.isMale ? "М" : "Ж",
		record.educationForm, dateToString(record.birthdayDate),
		dateToString(record.entranceDate), record.EGEPoints);
}

string Spreadsheet::recordToFileString(Record record) 
{
	return format("{} {} {} {} {} {} {} {}",
		record.groupCode, record.personalId, record.name, record.isMale ? "М" : "Ж",
		record.educationForm, dateToFileString(record.birthdayDate),
		dateToFileString(record.entranceDate), record.EGEPoints);
}

string Spreadsheet::nodeToString(Node* node)
{
	return recordToString(node->record);
}

string Spreadsheet::nodeToFileString(Node* node)
{
	return recordToFileString(node->record);
}

void Spreadsheet::display()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int rows = csbi.srWindow.Bottom - csbi.srWindow.Top - 5;
	Node* showList = list;
	int currentPage = 0;
	int ch;
	bool exit = false;
	bool forward = true;

	system("cls");
	displayPage(showList, rows, 0);

	while (!exit)
	{
		ch = _getch();
		switch (ch)
		{
		case 224:
		{
			switch (_getch())
			{
			case 75:
			{// нажата клавиша влево
				if (currentPage > 0)
				{
					system("cls");
					showList = list;
					currentPage--;
					forward = displayPage(showList, rows, currentPage);
				}
				break;
			}
			case 77:
			{// нажата клавиша вправо
				if (forward)
				{
					system("cls");
					showList = list;
					currentPage++;
					forward = displayPage(showList, rows, currentPage);
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

	showList = nullptr;
}

bool Spreadsheet::displayPage(Node* showList, int rows, int page) {
	if (showList == NULL) {
		cout << "Таблица пуста" << endl;
		cout << "Нажмите ESC для завершения просмотра";
		return false;
	}

	for (int i = 0; i < rows * page; i++) 
	{
		if (showList == NULL) return false;
		else showList = showList -> next;
	}

	if (showList != NULL) {
		cout << "Таблица: " << tableName << ", Страница - " << page + 1 << endl;
		printHeader();
		while (showList) {
			if (rows <= 0) break;
			cout << nodeToString(showList) << endl;
			showList = showList -> next;
			rows--;
		}
		printBottom();
		cout << "Нажмите ESC для завершения просмотра";
		if (rows > 0 || showList == NULL) return false;
	}

	return true;
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
					if (compareDate(array[i]->record.birthdayDate, maxArrDate) > 0)
					{
						maxArrDate = array[i]->record.birthdayDate;
						index = i;
					}
				}
				if (compareDate(head->record.birthdayDate, array[index]->record.birthdayDate) < 0)
				{
					array[index] = head;
				}
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

	cout << "Cтаршие юноши:" << endl;
	printHeader();

	for (int i = 0; i < 5; i++)
	{
		if (males[i])
			cout << nodeToString(males[i]) << endl;
	}
	printBottom();

	cout << endl << "Cтаршие девушки:" << endl;
	printHeader();
	for (int i = 0; i < 5; i++)
	{
		if (females[i])
			cout << nodeToString(females[i]) << endl;
	}
	printBottom();

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
			out << nodeToFileString(head) << endl;
			head = head->next;
		}
	}

	head = nullptr;
}

void Spreadsheet::readFromFile(string fileName)
{
	tableName = fileName;
	ifstream in(format("{}.bin", fileName));
	Record r = Record();

	if (in.is_open())
	{
		while (in >> r)
		{
			addRecord(r);
		}
	}
}