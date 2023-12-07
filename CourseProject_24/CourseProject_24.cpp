#include <iostream>
#include <fstream>
#include <format>
#include <Windows.h>
#include <conio.h>
#include "Spreadsheet.h"
#pragma warning(disable : 4996)


using namespace std;

Spreadsheet s;
const int* menuSizes = new int[] { 4, 2, 8, 2, 2, 8 };

//SREADSHEET
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

void printHeader()
{
	cout << "+-------------+------------+---------------------+-----+-------------+------------+------------------+-----------+" << endl
		<< "| Шифр группы | Номер зач. |         ФИО         | Пол | Форма обуч. | Дата рожд. | Дата поступления | Баллы ЕГЭ |" << endl
		<< "+-------------+------------+---------------------+-----+-------------+------------+------------------+-----------+" << endl;
}

void printBottom()
{
	cout << "+-------------+------------+---------------------+-----+-------------+------------+------------------+-----------+" << endl;
}

int compareDate(Date date, Date date2)
{
	if (date.year > date2.year) return  1;
	else if (date.year < date2.year) return -1;
	if (date.month > date2.month) return 1;
	else if (date.month < date2.month) return -1;
	if (date.day > date2.day) return 1;
	else if (date.day < date2.day) return -1;
	else return 0;
}

string dateToString(Date date)
{
	return format("{:02}.{:02}.{}", date.day, date.month, date.year);
}

string dateToFileString(Date date)
{
	return format("{} {} {}", date.day, date.month, date.year);
}

bool operator > (const Record& record, const Record& record2)
{
	return strcmp(record.groupCode.c_str(), record2.groupCode.c_str()) > 0;
}

bool operator < (const Record& record, const Record& record2)
{
	return strcmp(record.groupCode.c_str(), record2.groupCode.c_str()) < 0;
}

string recordToString(Record record)
{
	return format("|   {:<9} | {:<10} | {:<19} |  {:<1}  |   {:<9} | {:<10} |    {:<13} |    {:<6} |",
		record.groupCode, record.personalId, record.name, record.isMale ? "М" : "Ж",
		record.educationForm, dateToString(record.birthdayDate),
		dateToString(record.entranceDate), record.EGEPoints);
}

string recordToFileString(Record record)
{
	cout << record.name.size() << endl;
	return format("{} {} {} {} {} {} {} {}",
		record.groupCode, record.personalId, record.name, record.isMale ? "М" : "Ж",
		record.educationForm, dateToFileString(record.birthdayDate),
		dateToFileString(record.entranceDate), record.EGEPoints);
}

string nodeToString(Node* node)
{
	return recordToString(node->record);
}

string nodeToFileString(Node* node)
{
	string r = recordToFileString(node->record);
	return r;
}

bool displayPage(Node* showList, int rows, int page) {
	if (showList == NULL) {
		cout << "Таблица пуста" << endl;
		cout << "Нажмите ESC для завершения просмотра";
		return false;
	}

	for (int i = 0; i < rows * page; i++)
	{
		if (showList == NULL) return false;
		else showList = showList->next;
	}

	if (showList != NULL) {
		cout << "Таблица: " << s.tableName << ", Страница - " << page + 1 << endl;
		printHeader();
		while (showList) {
			if (rows <= 0) break;
			cout << nodeToString(showList) << endl;
			showList = showList->next;
			rows--;
		}
		printBottom();
		cout << "Нажмите ESC для завершения просмотра";
		if (rows > 0 || showList == NULL) return false;
	}

	return true;
}

void display()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int rows = csbi.srWindow.Bottom - csbi.srWindow.Top - 5;
	Node* showList = s.list;
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
					showList = s.list;
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
					showList = s.list;
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

void addRecord(Record record)
{
	Node* newElem = new Node{ record, s.list };
	s.list = newElem;

	newElem = nullptr;
}

Record getRecordFromStream(istream& in)
{
	Record r;
	in >> r;

	return r;
}

bool removeRecord(int personalId)
{
	Node* head = s.list;

	if (head != NULL)
	{
		if (s.list->record.personalId == personalId)
		{
			s.list = s.list->next;
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

bool editRecord(int personalId, int fieldNum, string value)
{
	Node* head = s.list;

	if (head != NULL)
	{
		while (head) {
			if (head->record.personalId == personalId)
			{
				Record r = head->record;
				switch (fieldNum) {
					case 0:
					{
						r.groupCode = value;
						break;
					}
					case 1: 
					{
						try {
							r.personalId = stoi(value);
						}
						catch (...) {}
						break;
					}
					case 2:
					{
						r.name = value;
						break;
					}
					case 3:
					{
						r.isMale = (value == "М") ? true : false;
						break;
					}
					case 4:
					{
						r.educationForm = value;
						break;
					}
					case 5:
					{
						int index = value.find_first_of(".");
						short day = stoi(value.substr(0, index));
						value = value.substr(index + 1, value.size());
						index = value.find_first_of(".");
						short month = stoi(value.substr(0, index));
						value = value.substr(index + 1, value.size());
						short year = stoi(value);
						r.birthdayDate = Date{year, month, day};
						break;
					}
					case 6:
					{
						int index = value.find_first_of(".");
						short day = stoi(value.substr(0, index));
						value = value.substr(index + 1, value.size());
						index = value.find_first_of(".");
						short month = stoi(value.substr(0, index));
						value = value.substr(index + 1, value.size());
						short year = stoi(value);
						r.entranceDate = Date{ year, month, day };
						break;
					}
					case 7:
					{
						try {
							r.EGEPoints = stoi(value);
						}
						catch (...) {}
						break;
					}
				}
				
				head->record = r;

				head = nullptr;
				return true;
			}

			head = head->next;
		}
	}

	head = nullptr;
	return false;
}

void sortAsc() //пузырьковая сортировка
{
	Node* t, * m, * a, * b;
	if (s.list == NULL) return;

	for (bool go = true; go; ) {
		go = false;
		a = t = s.list;
		b = s.list->next;

		while (b != NULL) {
			if (a->record > b->record) {
				if (t == a)
					s.list = b;
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

void sortDesc() //пузырьковая сортировка
{
	Node* t, * m, * a, * b;
	if (s.list == NULL) return;

	for (bool go = true; go; ) {
		go = false;
		a = t = s.list;
		b = s.list->next;

		while (b != NULL) {
			if (a->record < b->record) {
				if (t == a)
					s.list = b;
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

Node* seek(int personalId)
{
	Node* head = s.list;

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

void getFiveEldest(Node** array, bool isMale)
{
	Node* head = s.list;
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

void getFiveEldest()
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

void saveToFile(string fileName, string extension)
{
	ofstream out;
	out.open(format("{}.{}", fileName, extension));
	Node* head = s.list;

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

void readFromFile(string fileName)
{
	int index = fileName.find_first_of(".");
	s.tableName = fileName.substr(0,index);
	ifstream in(fileName);
	Record r = Record();

	if (in.is_open())
	{
		while (in >> r)
		{
			addRecord(r);
		}
	}
} //SPREADSHEET END

//MENU
void printMenu(int num, int position)
{
	const int size = menuSizes[num];
	const string* first = new string[]{
		"Создание новой таблицы",
		"Загрузка таблицы из файла",
		"Сохранение текущей таблицы в файл",
		"Выход из программы"
	};
	const string* second = new string[]{
		"Выход из программы",
		"Продолжить работу с таблицей"
	};
	const string* third = new string[]{
		"Вернуться в главное меню",
		"Просмотр таблицы",
		"Добавить запись",
		"Удалить запись",
		"Изменить запись",
		"Сортировать таблицу",
		"Найти запись",
		"Получить 5 старших юношей и девушек"
	};
	const string* fourth = new string[]{
		"Сохранить в файл формата *.bin",
		"Сохранить в файл формата *.sheet"
	};
	const string* fifth = new string[]{
		"Сортировка по возрастанию",
		"Сортировка по убыванию"
	};
	const string* sixth = new string[]{
		"Шифр группы",
		"Номер зачетной книжки",
		"ФИО",
		"Пол (М/Ж)",
		"Форма обучения",
		"Дата рождения",
		"Дата поступления",
		"Баллы ЕГЭ"
	};

	switch (num)
	{
	case 0:
		cout << "Список команд:" << endl;
		for (int i = 0; i < size; i++) {
			if (i == position) {
				cout << "-> ";
			}
			cout << first[i] << endl;
		}
		break;
	case 1:
		cout << "Список команд:" << endl;
			for (int i = 0; i < size; i++) {
				if (i == position) {
					cout << "-> ";
				}
				cout << second[i] << endl;
			}
		break;
	case 2:
		cout << "Список команд:" << endl;
		for (int i = 0; i < size; i++) {
			if (i == position) {
				cout << "-> ";
			}
			cout << third[i] << endl;
		}
		break;
	case 3:
		cout << "Список команд:" << endl;
		for (int i = 0; i < size; i++) {
			if (i == position) {
				cout << "-> ";
			}
			cout << fourth[i] << endl;
		}
		break;
	case 4:
		cout << "Список команд:" << endl;
		for (int i = 0; i < size; i++) {
			if (i == position) {
				cout << "-> ";
			}
			cout << fifth[i] << endl;
		}
		break;
	case 5:
		cout << "Выберите поле для изменения:" << endl;
		for (int i = 0; i < size; i++) {
			if (i == position) {
				cout << "-> ";
			}
			cout << sixth[i] << endl;
		}
		break;
	}
	
}

//int getCommand(int count)
//{
//	int variant;
//	string s; // строка для считывания введённых данных
//	getline(cin, s); // считываем строку
//	while (s.empty())
//	{
//		getline(cin, s);
//	}
//
//	// пока ввод некорректен, сообщаем об этом и просим повторить его
//	while (sscanf(s.c_str(), "%d", &variant) != 1 || variant < 0 || variant > count) {
//		cout << "Неправильный код: " << endl; // выводим сообщение об ошибке
//		getline(cin, s); // считываем строку повторно
//	}
//
//	return variant;
//}

int positionPicker(int menuId, int menuSize, string defaultText) {
	int position = 0;
	int ch;
	bool exit = false;
	system("cls");
	if (defaultText != "") {
		printHeader();
		cout << defaultText << endl;
		printBottom();
	}
	printMenu(menuId, position);

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
			{// нажата клавиша вверх
				if (position > 0) {
					position -= 1;
					system("cls");
					if (defaultText != "") {
						printHeader();
						cout << defaultText << endl;
						printBottom();
					}
					printMenu(menuId, position);
				}
				break;
			}
			case 75:
			{// нажата клавиша влево
				if (position > 0) {
					position -= 1;
					system("cls");
					if (defaultText != "") {
						printHeader();
						cout << defaultText << endl;
						printBottom();
					}
					printMenu(menuId, position);
				}
				break;
			}
			case 80:
			{// нажата клавиша вниз
				if (position < menuSize - 1) {
					position += 1;
					system("cls");
					if (defaultText != "") {
						printHeader();
						cout << defaultText << endl;
						printBottom();
					}
					printMenu(menuId, position);
				}
				break;
			}
			case 77:
			{// нажата клавиша вправо
				if (position < menuSize - 1) {
					position += 1;
					system("cls");
					if (defaultText != "") {
						printHeader();
						cout << defaultText << endl;
						printBottom();
					}
					printMenu(menuId, position);
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		case 13:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
	}

	return position;
}

void operateWithTable()
{
	int command, numLine, pos;
	string line;
	Node* n = NULL;
	bool skip = false;
	int isAsc = -1;

	do
	{
		system("cls");

		command = positionPicker(2, menuSizes[2], "");
		//printMenu(3, 0);
		//command = getCommand(7);

		switch (command)
		{
		case 1:
			display();
			skip = true;
			break;
		case 2:
			cout << "Введите данные записи в формате:" << endl
				<< "ИТ22-6 123456 Балабанов В Е true очная 1 1 2008 1 1 2021 250" << endl;

			addRecord(getRecordFromStream(cin));
			display();
			skip = true;
			break;
		case 3:
			cout << "Введите номер зачетки для удаления записи:" << endl;
			cin >> numLine;
			removeRecord(numLine);
			display();
			skip = true;
			break;
		case 4:
			cout << "Введите номер зачетки для изменения записи:" << endl;
			cin >> numLine;
			//cout << "Введите новые данные записи в формате:" << endl
			//	<< "ИТ22-6 123456 Балабанов В Е true очная 1 1 2008 1 1 2021 250" << endl;
			system("cls");	
			n = seek(numLine);
			if (n != NULL)
			{
				line = nodeToString(n);
			}
			else
			{
				cout << "Запись не найдена" << endl;
				break;
			}
			pos = positionPicker(5, menuSizes[5], line);

			cout << "Введите новое значение поля:" << endl;
			cin.seekg(cin.eof());
			getline(cin, line);

			editRecord(numLine, pos, line);
			display();
			skip = true;
			break;
		case 5:
			isAsc = positionPicker(4, menuSizes[4], "");
			if (isAsc == 0)
			{
				sortAsc();
			}
			else {
				sortDesc();
			}
			display();
			skip = true;
			break;
		case 6:
			cout << "Введите номер зачетки для поиска записи:" << endl;
			cin >> numLine;
			n = seek(numLine);
			if (n != NULL)
			{
				cout << "Искомая запись:" << endl;
				printHeader();
				cout << nodeToString(n) << endl;
				printBottom();
			}
			else
			{
				cout << "Запись не найдена" << endl;
			}
			break;
		case 7:
			getFiveEldest();
			break;
		}
		if (command != 0)
		{
			if (!skip)
			{
				system("pause");
			}
			else {
				skip = false;
			}
		}
	} while (command != 0);

	n = nullptr;
}

void saveToFile(bool leave)
{
	string fileName;
	int command;

	cout << "Введите имя файла для сохранения" << endl;
	cin >> fileName;

	command = positionPicker(3, menuSizes[3], "");
	saveToFile(fileName, (command == 0) ? "bin" : "sheet");

	if (!leave) {
		do
		{
			system("cls");
			command = positionPicker(1, menuSizes[1], "");
			//printMenu(2, 0);
			//command = getCommand(1);

			switch (command)
			{
			case 1:
				operateWithTable();
				break;
			}
		} while (command != 0);
	}
	exit(0);
}

void loadFromFile()
{
	string fileName;

	cout << "Введите полное имя файла для открытия" << endl;
	cin >> fileName;

	readFromFile(fileName);
	operateWithTable();
}

void startMenu()
{
	int command;
	string tableName;

	do
	{
		system("cls");
		command = positionPicker(0, menuSizes[0], "");
		//printMenu(1, 0);
		//command = getCommand(3);

		switch (command)
		{
		case 0:
			cout << "Введите название таблицы:" << endl;
			cin >> tableName;

			s = Spreadsheet(tableName);
			operateWithTable();
			break;
		case 1:
			loadFromFile();
			break;
		case 2:
			saveToFile(false);
			break;
		case 3:
			while (command != -1) {
				cout << "Сохранить таблицу в файл? (y/n)" << endl;
				char ch = _getch();
				cout << ch << endl;
				switch (ch)
				{
				case 'y':
					saveToFile(true);
					command = -1;
					break;
				case 'n':
					command = -1;
					break;
				default:
					break;
				}
			}
			break;
		}
	} while (command != -1);
} //MENU END

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);

	startMenu();
}