#pragma warning(disable : 4996)
#include "Menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <format>


Menu::Menu()
{
	Record r = Record("ИТ22-2", 1, format("Ф И О1"), false, format("очная"), Date(2001, 1, 1), Date(2021, 1, 1), 250);
	Record r2 = Record("ИТ22-3", 2, format("Ф И О2"), true, format("очная"), Date(2002, 1, 1), Date(2021, 1, 1), 250);
	Record r3 = Record("ИТ22-4", 3, format("Ф И О3"), false, format("очная"), Date(2003, 1, 1), Date(2021, 1, 1), 250);
	Record r4 = Record("ИТ22-5", 4, format("Ф И О4"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250);
	Record r5 = Record("ИТ22-6", 5, format("Ф И О5"), true, format("очная"), Date(2005, 1, 1), Date(2021, 1, 1), 250);
	Record r6 = Record("ИТ22-6", 6, format("Ф И О5"), true, format("очная"), Date(2006, 1, 1), Date(2021, 1, 1), 250);
	Record r7 = Record("ИТ22-6", 7, format("Ф И О5"), false, format("очная"), Date(2007, 1, 1), Date(2021, 1, 1), 250);
	Record r8 = Record("ИТ22-6", 8, format("Ф И О5"), true, format("очная"), Date(2008, 1, 1), Date(2021, 1, 1), 250);
	s = Spreadsheet();
	/*s.addRecord(r);
	s.addRecord(r2);
	s.addRecord(r3);
	s.addRecord(r4);
	s.addRecord(r5);
	s.addRecord(r6);
	s.addRecord(r7);
	s.addRecord(r8);*/
}

void printMenu(int num) 
{
	switch (num) 
	{
	case 1:
		cout << "Список команд:" << endl
			<< "1 - Создание новой таблицы" << endl
			<< "2 - Загрузка таблицы из файла" << endl
			<< "3 - Сохранение текущей таблицы в файл" << endl
			<< "0 - Выход из программы" << endl;
		break;
	case 2:
		cout << "Список команд:" << endl
			<< "1 - Продолжить работу с таблицей" << endl
			<< "0 - Выход из программы" << endl;
		break;
	case 3:
		cout << "Список команд:" << endl
			<< "1 - Просмотр таблицы" << endl
			<< "2 - Добавить запись" << endl
			<< "3 - Удалить запись" << endl
			<< "4 - Изменить запись" << endl
			<< "5 - Сортировать таблицу" << endl
			<< "6 - Найти запись" << endl
			<< "7 - Получить 5 старших юношей и девушек" << endl
			<< "0 - Вернуться в главное меню" << endl;
		break;
	}
}

void Menu::start()
{
	int command;
	string tableName;

	do
	{
		system("cls");

		printMenu(1);

		command = getCommand(3);

		switch (command)
		{
		case 1:
			cout << "Введите название таблицы:" << endl;
			cin >> tableName;

			s = Spreadsheet(tableName);
			operateWithTable();
			break;
		case 2:
			loadFromFile();
			break;
		case 3:
			saveToFile();
			break;
		}
	} while (command != 0);
}

void Menu::loadFromFile()
{
	string fileName;

	cout << "Введите имя файла для открытия" << endl;
	cin >> fileName;

	s.readFromFile(fileName);
	operateWithTable();
}

void Menu::saveToFile()
{
	string fileName;
	int command;

	cout << "Введите имя файла для сохранения" << endl;
	cin >> fileName;

	s.saveToFile(fileName);

	do
	{
		system("cls");
		printMenu(2);

		command = getCommand(1);

		switch (command)
		{
		case 1:
			operateWithTable();
			break;
		}
	} while (command != 0);
	exit(0);
}

void Menu::operateWithTable()
{
	int command, numLine;
	string line;
	Node* n = NULL;

	do
	{
		system("cls");

		printMenu(3);

		command = getCommand(7);

		switch (command)
		{
		case 1:
			s.display();
			break;
		case 2:
			cout << "Введите данные записи в формате:" << endl
				<< "ИТ22-6 123456 Балабанов В Е true очная 1 1 2008 1 1 2021 250" << endl;

			s.addRecord(s.getRecordFromStream(cin));
			s.display();
			break;
		case 3:
			cout << "Введите номер зачетки для удаления записи:" << endl;
			cin >> numLine;
			s.removeRecord(numLine);
			s.display();
			break;
		case 4:
			cout << "Введите номер зачетки для изменения записи:" << endl;
			cin >> numLine;
			cout << "Введите новые данные записи в формате:" << endl
				<< "ИТ22-6 123456 Балабанов В Е true очная 1 1 2008 1 1 2021 250" << endl;
			s.editRecord(numLine, s.getRecordFromStream(cin));
			s.display();
			break;	
		case 5:
			s.sort();
			s.display();
			break;
		case 6:
			cout << "Введите номер зачетки для поиска записи:" << endl;
			cin >> numLine;
			n = s.seek(numLine);
			if (n != NULL)
			{
				cout << "Искомая запись:" << endl
					<< n->toString() << endl;
			}
			else
			{
				cout << "Запись не найдена" << endl;
			}
			break;
		case 7:
			s.getFiveEldest();
			break;
		}
		if (command != 0)
		{
			system("pause");
		}
	} while (command != 0);

	delete n;
	n = nullptr;
}

int Menu::getCommand(int count)
{
	int variant;
	string s; // строка для считывания введённых данных
	getline(cin, s); // считываем строку
	while (s.empty()) 
	{
		getline(cin, s);
	}

	// пока ввод некорректен, сообщаем об этом и просим повторить его
	while (sscanf(s.c_str(), "%d", &variant) != 1 || variant < 0 || variant > count) {
		cout << "Неправильный код: " << endl; // выводим сообщение об ошибке
		getline(cin, s); // считываем строку повторно
	}

	return variant;
}